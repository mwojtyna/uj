import java.util.*;

class HistogramPatternMatcher extends AbstractHistogramPatternMatcher {
    private int min = Integer.MAX_VALUE;
    private int max = Integer.MIN_VALUE;
    private final Map<Integer, Integer> histogram = new HashMap<>();

    public static void main(String[] args) {
        {
            HistogramPatternMatcher h = new HistogramPatternMatcher();
            int[] data = new int[]{5, 3, 4, 2, 5, 5, 4, -1, -2, 2, 3, 4};
            for (int n : data) {
                h.data(n);
            }
            System.out.println(h.histogram());
            System.out.println(h.match(List.of(1, 1)));
            System.out.println(h.match(List.of(1, 0)));
        }
        System.out.println();
        {
            HistogramPatternMatcher h = new HistogramPatternMatcher();
            int[] data = new int[]{5, 3, 4, 2, 5, 5, 4, -1, -2, 2, 3, 4, 6, 6, 6, 6, 6, 6};
            for (int n : data) {
                h.data(n);
            }
            System.out.println(h.histogram());
            System.out.println(h.match(List.of(1, 1, 2)));
            System.out.println(h.match(List.of(1, 0, 0)));
            System.out.println(h.match(List.of(1, 2)));
        }
    }

    /**
     * Metoda umożliwia użytkownikowi wprowadzanie danych.
     *
     * @param value wprowadzana przez użytkownika liczba
     */
    @Override
    public void data(int value) {
        min = Math.min(min, value);
        max = Math.max(max, value);
        histogram.put(value, histogram.getOrDefault(value, 0) + 1);
    }

    /**
     * Metoda zwraca histogram. Histogram nie może zawierać pozycji zawierających
     * zero zliczeń. Jeśli wywołanie metody nastąpi przed prowadzeniem danych metoda
     * zwraca pustą mapę (mapę o rozmiarze 0). Metoda nigdy nie zwraca NULL.
     *
     * @return mapa reprezentująca histogram. Klucz to liczba, wartość wskazywana
     * kluczem, to liczba wystąpień danej liczby we wprowadzanych danych.
     */
    @Override
    public Map<Integer, Integer> histogram() {
        return histogram;
    }

    /**
     * Metoda zwraca zbiór kluczy z histogramu. Do zbioru wprawdzane są te klucze,
     * od których zaczyna się sekwencja zliczeń, która pasuje do wskazanego wzorca.
     * Wzorzec należy rozumieć na zasadzie proporcji pomiędzy kolejnymi zliczeniami.
     * Wzorzec: [2,1,2] pasować będzie np. do sekwencji zliczeń 10:5:10 czy 4:2:4,
     * jednocześnie wzorzec ten nie pasuje np. do 11:5:10. Brak odpowiedzi metoda
     * sygnalizuje zwracając zbiór pusty. Metoda nigdy nie zwraca NULL.
     *
     * @param pattern wzorzec kolejnych zliczeń w histogramie
     * @return zbiór liczby rozpoczynających sekwencję zliczeń
     */
    @Override
    public Set<Integer> match(List<Integer> pattern) {
        Set<Integer> res = new HashSet<>();

        for (int n = min; n <= max && n + pattern.size() - 1 <= max; n++) {
            if (segmentMatched(n, pattern)) {
                res.add(n);
            }
        }

        return res;
    }

    private boolean segmentMatched(int start, List<Integer> pattern) {
        int startFreq = histogram.getOrDefault(start, 0);

        for (int i = 1; i < pattern.size(); i++) {
            int curFreq = histogram.getOrDefault(start + i, 0);

            // Only patterns 1:1:..., 2:2:..., etc. should match [0, 0, ...]
            if (!pattern.get(i).equals(pattern.getFirst()) && startFreq == 0 && curFreq == 0) {
                return false;
            }
            if (curFreq != pattern.get(i) * startFreq) {
                return false;
            }
        }

        return true;
    }
}
