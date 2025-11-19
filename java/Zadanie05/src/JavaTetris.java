import java.util.Arrays;
import java.util.List;
import java.util.Set;

public class JavaTetris implements Tetris {
    private int rows;
    private int cols;
    /// Lowest free box in ith column
    private int[] lowestFree;

    public static void main(String[] args) {
        {
            JavaTetris tetris = new JavaTetris();
            tetris.cols(11);
            tetris.rows(18);
            Block block1 = new Block() {
                @Override
                public Position base() {
                    return new Position(2, 15);
                }

                @Override
                public Set<Vector> squares() {
                    return Set.of(new Vector[]{new Vector(-1, 1), new Vector(1, 1), new Vector(2, 2)});
                }
            };
            Block block2 = new Block() {
                @Override
                public Position base() {
                    return new Position(3, 15);
                }

                @Override
                public Set<Vector> squares() {
                    return Set.of(new Vector[]{new Vector(-1, 1), new Vector(1, 1), new Vector(2, 2)});
                }
            };
            tetris.drop(block1);
            tetris.drop(block2);
        }
    }

    @Override
    public void rows(int rows) {
        this.rows = rows;
        this.lowestFree = new int[this.cols];
    }

    @Override
    public void cols(int cols) {
        this.cols = cols;
        this.lowestFree = new int[this.cols];
    }

    @Override
    public void drop(Block block) {
        int rowOffset = calculateDropHeight(block);
        this.lowestFree[block.base().col()] = block.base().row() - rowOffset + 1;
        for (Vector dv : block.squares()) {
            int newRow = block.base().row() + dv.dRow() - rowOffset;
            this.lowestFree[block.base().col() + dv.dCol()] = newRow + 1;
        }

        // TODO: Clear row when full
    }

    @Override
    public void optimalDrop(Block block) {
        // Iterate through all **valid** columns (where the block doesn't stick out of bounds),
        // and drop the one where calculateDropHeight is the smallest
    }

    @Override
    public List<Integer> state() {
        return Arrays.stream(this.lowestFree).boxed().map(i -> {
            if (i > 0) {
                return i - 1;
            } else {
                return 0;
            }
        }).toList();
    }

    /// @return The number of rows the block has to fall until it encounters another block
    private int calculateDropHeight(Block block) {
        int min = block.base().row() - this.lowestFree[block.base().col()];
        for (var pos : block.squares()) {
            min = Math.min(min, block.base().row() + pos.dRow() - this.lowestFree[block.base().col() + pos.dCol()]);
        }
        return min;
    }
}
