import java.util.Arrays;

/**
 * Klasa abstrakcyjna prezentująca metody obsługi ciągu liczb.
 */
abstract class AbstractSequence {
    /**
     * Ustawienie danych, dla których wykonywane będą kolejne operacje. Ponowne
     * wykonanie metody powoduje zmianę obsługiwanego zestawu danych. Dane zapisane
     * są w postaci (kolejne pozycje tablicy):
     *
     * <pre>
     * dana delta1 delta2 ... deltaN dana delta1 delta2 ... deltaN itd.
     * </pre>
     * <p>
     * W powyższy sposób zakodowany jest pewien ciąg liczb. Idea kodowania polega na
     * tym, że oryginalny ciąg liczb dzielony jest na fragmenty (podciągi) o
     * rozmiarze N+1. Pierwsza liczba w podciągu podawana jest wprost. Kolejne N
     * liczb to różnice pomiedzy kolejnymi liczbami ciągu. I tak:
     *
     * <pre>
     * indeks   tablica wejściowa    odkodowany ciąg
     * 0           data[0]             data[0]
     * 1           data[1]             data[0]+data[1]
     * 2           data[2]             data[0]+data[1]+data[2]
     * .           .
     * .           .
     * N           data[N]             data[0]+data[1]+data[2]+...+data[N]
     * N+1         data[N+1]           data[N+1]
     * N+2         data[N+2]           data[N+1]+data[N+2]
     * N+2         data[N+3]           data[N+1]+data[N+2]+data[N+3]
     * itd.
     * </pre>
     * <p>
     * Nie ma gwarancji, że wszystkie podciągi są używane w całości. Ostatni może
     * zawierać mniej niż N delt. Czyli, rozmiar tablicy data nie musi być całkowitą
     * wielokrotnością (deltaSegmentSize+1).
     *
     * @param data             tablica zawierająca dane
     * @param deltaSegmentSize rozmiar segmentu zawierającego delty
     *                         (deltaSegmentSize = N). Podciąg ma efektywnie długość
     *                         deltaSegmentSize+1
     *
     */
    abstract public void sequence(int[] data, int deltaSegmentSize);

    /**
     * Metoda zwraca odkodowany ciąg.
     *
     * @return odkodowany ciąg
     */
    abstract public int[] decode();

    /**
     * Metoda koduje otrzymany metodą sequence ciąg dostosowując wynik do podanej
     * długości segmentu zawierającego delta.
     *
     * @param deltaSegmentSize
     * @return ciąg zakodowany z podanym rozmiarem segmentu zawierającego delty.
     */
    abstract public int[] encode(int deltaSegmentSize);

    /**
     * Metoda sprawdza, czy podany ciąg liczb jest równoważny temu, który wcześniej
     * otrzymano za pomocą sequence. Metoda uwzględnia zawartość ciągu liczb jak i
     * jego długość.
     *
     * @param data             dane nowego ciągu liczb
     * @param deltaSegmentSize rozmiar segmentu delt
     * @return prawda - odkodowane ciągi liczb są równie, false - odkodowane ciągi
     * liczb do siebie nie pasują.
     */
    abstract public boolean equals(int[] data, int deltaSegmentSize);
}

public class Sequence extends AbstractSequence {
    // Encoded
    private int[] data;
    private int deltaSegmentSize;

    public static void main(String[] args) {
        AbstractSequence s = new Sequence();
        int[] original = new int[]{10, 5, -3, 2, 20, 2, 8, 1, 31, -1, 70, 20};
        s.sequence(original, 3);

        int[] decoded = s.decode();
        int[] encoded = s.encode(3);
        int[] encoded4 = s.encode(4);
        System.out.println("original: " + Arrays.toString(original));
        System.out.println("decoded: " + Arrays.toString(decoded));
        System.out.println("encoded: " + Arrays.toString(encoded));
        System.out.println("encoded(4): " + Arrays.toString(encoded4));
        System.out.println("equals: " + s.equals(encoded4, 4));
    }

    public void sequence(int[] data, int deltaSegmentSize) {
        this.data = data;
        this.deltaSegmentSize = deltaSegmentSize;
    }

    public int[] decode() {
        int[] decoded = new int[data.length];

        for (int i = 0; i < data.length; i += deltaSegmentSize + 1) {
            // Wypełnij początek segmentu
            decoded[i] = data[i];

            // Dekoduj segment
            for (int j = i + 1; j - i <= deltaSegmentSize && j < data.length; j++) {
                decoded[j] = decoded[j - 1] + data[j];
            }
        }

        return decoded;
    }

    public int[] encode(int deltaSegmentSize) {
        if (deltaSegmentSize == this.deltaSegmentSize) {
            return this.data;
        }

        int[] decoded = decode();
        int[] encoded = new int[decoded.length];

        for (int i = 0; i < decoded.length; i += deltaSegmentSize + 1) {
            // Wypełnij początek segmentu
            encoded[i] = decoded[i];

            // Enkoduj segment
            for (int j = i + 1; j - i <= deltaSegmentSize && j < decoded.length; j++) {
                encoded[j] = decoded[j] - decoded[j - 1];
            }
        }

        return encoded;
    }

    public boolean equals(int[] data, int deltaSegmentSize) {
        int[] myDecoded = decode();
        Sequence theirs = new Sequence();
        theirs.sequence(data, deltaSegmentSize);
        int[] theirsDecoded = theirs.decode();

        return Arrays.equals(myDecoded, theirsDecoded);
    }
}
