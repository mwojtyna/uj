import java.util.Arrays;

class Sequence extends AbstractSequence {
    // Encoded
    private int[] data;
    private int deltaSegmentSize;

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
