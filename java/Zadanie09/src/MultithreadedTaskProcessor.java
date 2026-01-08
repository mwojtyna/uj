import java.util.*;
import java.util.concurrent.*;

public class MultithreadedTaskProcessor implements TaskProcessor {
    private int threadsLimit;

    @Override
    public void threadsLimit(int limit) {
        this.threadsLimit = limit;
    }

    @Override
    public void set(List<Task> tasks, ThreadsFactory factory, ResultConsumer consumer) {
        if (tasks.isEmpty()) {
            return;
        }

        int N = tasks.size();
        BlockingQueue<TaskWithIdx> taskQueue = new ArrayBlockingQueue<>(N);
        Result[] results = new Result[N];
        Object saveLock = new Object();

        for (int i = 0; i < N; i++) {
            taskQueue.add(new TaskWithIdx(tasks.get(i), i));
        }

        Thread saver = new Thread(() -> {
            int next = 0;
            try {
                while (next < N) {
                    synchronized (saveLock) {
                        while (results[next] == null) {
                            saveLock.wait();
                        }

                        Result r = results[next];
                        consumer.save(r.taskId(), r.value());
                        next++;
                    }
                }
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        });
        saver.start();

        List<Runnable> workers = new ArrayList<>();
        for (int i = 0; i < threadsLimit; i++) {
            workers.add(new Worker(taskQueue, results, saveLock));
        }

        List<Thread> threads = factory.createThreads(workers);
        for (var thread : threads) {
            thread.start();
        }
        for (var thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        try {
            saver.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    class Worker implements Runnable {
        private final BlockingQueue<TaskWithIdx> taskQueue;
        private final Result[] results;
        private final Object saveLock;

        public Worker(BlockingQueue<TaskWithIdx> taskQueue, Result[] results, Object saveLock) {
            this.taskQueue = taskQueue;
            this.results = results;
            this.saveLock = saveLock;
        }

        @Override
        public void run() {
            while (true) {
                TaskWithIdx taskWithIdx = taskQueue.poll();
                if (taskWithIdx == null) {
                    break;
                }

                int resultValue = taskWithIdx.task().result();
                synchronized (saveLock) {
                    results[taskWithIdx.idx()] = new Result(taskWithIdx.task().id(), resultValue);
                    saveLock.notifyAll();
                }
            }
        }
    }

    record TaskWithIdx(Task task, int idx) {
    }

    record Result(int taskId, int value) {
    }
}
