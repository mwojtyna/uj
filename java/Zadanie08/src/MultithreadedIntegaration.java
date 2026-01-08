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

        CalcIntegralPoint[] calculators = new CalcIntegralPoint[this.threadsNum];
        Thread[] threads = new Thread[this.threadsNum];
        for (int i = 0; i < threads.length; i++) {
            calculators[i] = new CalcIntegralPoint(this.nextIndex, this.f, dx, range.min(), subintervals);
            threads[i] = new Thread(calculators[i]);
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

        for (var calculator : calculators) {
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
}

class CalcIntegralPoint implements Runnable {
    private final AtomicInteger nextIndex;
    private final Function<Double, Double> f;
    private final double dx;
    private final double rangeMin;
    private final int N;
    private double sum;

    public CalcIntegralPoint(AtomicInteger nextIndex, Function<Double, Double> f, double dx, double rangeMin, int N) {
        this.nextIndex = nextIndex;
        this.f = f;
        this.dx = dx;
        this.rangeMin = rangeMin;
        this.N = N;
    }

    public double getSum() {
        return this.sum;
    }

    @Override
    public void run() {
        while (true) {
            int i = this.nextIndex.getAndIncrement();
            if (i >= N) {
                break;
            }
            double x = this.rangeMin + (i + 0.5) * dx;
            double dy = this.f.apply(x);
            this.sum += this.dx * dy;
        }
    }
}
