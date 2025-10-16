import java.util.Arrays;

public class Sequence extends AbstractSequence {
    // Encoded
    private int[] data;
    private int deltaSegmentSize;

    public static void main(String[] args) {
        int[] data1 = {1, 2, 3};
        int[] data2 = {1, 2, 3};
        AbstractSequence sequence = new Sequence();
        sequence.sequence(data2, 3);

        int[] decoded = sequence.decode();
        int[] encoded = sequence.encode(3);
        System.out.println(sequence.equals(data2, 3));
        System.out.println(sequence.equals(data2, 2));
        System.out.println(Arrays.toString(decoded));
        System.out.println(Arrays.toString(encoded));

        sequence.sequence(data1, 2);
        decoded = sequence.decode();
        encoded = sequence.encode(2);
        System.out.println(sequence.equals(data1, 2));
        System.out.println(sequence.equals(data1, 1));
        System.out.println(Arrays.toString(decoded));
        System.out.println(Arrays.toString(encoded));

        sequence.sequence(data1, 1);
        decoded = sequence.decode();
        encoded = sequence.encode(1);
        System.out.println(sequence.equals(data1, 1));
        System.out.println(Arrays.toString(decoded));
        System.out.println(Arrays.toString(encoded));

        sequence.sequence(data1, 0);
        decoded = sequence.decode();
        encoded = sequence.encode(0);
        System.out.println(sequence.equals(data1, 0));
        System.out.println(Arrays.toString(decoded));
        System.out.println(Arrays.toString(encoded));

        sequence.sequence(data1, 12);
        decoded = sequence.decode();
        encoded = sequence.encode(12);
        System.out.println(sequence.equals(data1, 12));

        sequence.sequence(data1, 13);
        decoded = sequence.decode();
        encoded = sequence.encode(13);
        System.out.println(sequence.equals(data1, 13));
    }

    @Override
    public void sequence(int[] data, int deltaSegmentSize) {
        this.data = data;
        this.deltaSegmentSize = deltaSegmentSize;
    }

    @Override
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

    @Override
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

    @Override
    public boolean equals(int[] data, int deltaSegmentSize) {
        int[] myDecoded = decode();
        Sequence theirs = new Sequence();
        theirs.sequence(data, deltaSegmentSize);
        int[] theirsDecoded = theirs.decode();

        return Arrays.equals(myDecoded, theirsDecoded);
    }
}
