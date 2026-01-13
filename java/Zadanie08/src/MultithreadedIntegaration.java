import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.Function;

public class MultithreadedIntegaration implements ParallelIntegaration {
    private Function<Double, Double> f;
    private int threadsNum = 0;
    private final AtomicInteger nextIndex = new AtomicInteger(0);
    private double result = 0;

    /**
     * Metoda ustawia funkcję, której całkę trzeba policzyć.
     *
     * @param function funkcja do scałkowania
     */
    @Override
    public void setFunction(Function<Double, Double> function) {
        this.f = function;
    }

    /**
     * Metoda ustawia liczbę wątków jaką wolno użyć do równoległego liczenia całki.
     *
     * @param threads liczba wątków
     */
    @Override
    public void setThreadsNumber(int threads) {
        this.threadsNum = threads;
    }

    /**
     * Metoda zleca wykonanie rachunku. Całka wyznaczana jest metodą prostokątów.
     * Liczbę podprzedziałów przekazuje ta metoda. Liczba podprzedziałów będzie
     * większa od liczby wątków.
     *
     * @param range        przedział, w jakim całkę należy policzyć
     * @param subintervals liczba przedziałów
     */
    @Override
    public void calc(Range range, int subintervals) {
        // Reset
        this.result = 0;
        this.nextIndex.set(0);

        double dx = (range.max() - range.min()) / subintervals;
        int intervalSize = Math.max(1, subintervals / (this.threadsNum * 20));

        CalcIntegralPoint[] workers = new CalcIntegralPoint[this.threadsNum];
        Thread[] threads = new Thread[this.threadsNum];
        for (int i = 0; i < threads.length; i++) {
            workers[i] = new CalcIntegralPoint(dx, range.min(), intervalSize, subintervals);
            threads[i] = new Thread(workers[i]);
        }

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

        for (var calculator : workers) {
            this.result += calculator.getSum();
        }
    }

    /**
     * Metoda zwraca wynik rachunku.
     *
     * @return wynik rachunku
     */
    @Override
    public double getResult() {
        return this.result;
    }

    class CalcIntegralPoint implements Runnable {
        private final double dx;
        private final double rangeMin;
        private final int intervalSize;
        private final int N;
        private double sum;

        public CalcIntegralPoint(double dx, double rangeMin, int intervalSize, int N) {
            this.dx = dx;
            this.rangeMin = rangeMin;
            this.intervalSize = intervalSize;
            this.N = N;
        }

        public double getSum() {
            return this.sum;
        }

        @Override
        public void run() {
            while (true) {
                int start = nextIndex.getAndAdd(intervalSize);
                if (start >= N) {
                    break;
                }

                int end = Math.min(start + this.intervalSize, N);
                for (int i = start; i < end; i++) {
                    double mid = this.rangeMin + i * this.dx;
                    double dy = f.apply(mid);
                    this.sum += this.dx * dy;
                }
            }
        }
    }
}

