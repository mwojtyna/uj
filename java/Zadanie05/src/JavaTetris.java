import java.util.*;

public class JavaTetris implements Tetris {
    /// 1-indexed
    private int rows;
    /// 0-indexed
    private int cols;
    private boolean[][] grid;

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
            tetris.printGrid();
            tetris.drop(block2);
            tetris.printGrid();
        }
    }

    @Override
    public void rows(int rows) {
        this.rows = rows;
        this.grid = new boolean[this.rows][this.cols];
    }

    @Override
    public void cols(int cols) {
        this.cols = cols;
        this.grid = new boolean[this.rows][this.cols];
    }

    @Override
    public void drop(Block block) {
        List<Position> positions = fromOramusBlock(block);

        for (int dRow = 0; dRow < this.rows; dRow++) {
            for (Position pos : positions) {
                if (pos.row() + dRow + 1 >= this.rows || this.grid[pos.row() + dRow + 1][pos.col()]) {
                    placeBlock(positions, dRow);
                    return;
                }
            }
        }

        // Didn't place block, but it has to
        assert false;
    }

    @Override
    public void optimalDrop(Block block) {
        // Iterate through all **valid** columns (where the block doesn't stick out of bounds),
        // and drop the one where calculateDropHeight is the smallest
    }

    @Override
    public List<Integer> state() {
        return List.of();
    }

    /// @param dRow change of row
    private void placeBlock(List<Position> block, int dRow) {
        for (Position pos : block) {
            assert !this.grid[pos.row() + dRow][pos.col()];
            this.grid[pos.row() + dRow][pos.col()] = true;
        }
    }

    private List<Position> fromOramusBlock(Block block) {
        List<Position> res = new ArrayList<>(block.squares().size() + 1);

        int baseRow = fromOramusRow(block.base().row());
        int baseCol = block.base().col();

        res.add(new Position(baseCol, baseRow));
        for (Vector dv : block.squares()) {
            res.add(new Position(baseCol + dv.dCol(), baseRow - dv.dRow()));
        }

        return res;
    }
    private int fromOramusRow(int row) {
        return this.rows - row;
    }

    /// Prints grid in Oramus coordinates, placing X where there is a block
    private void printGrid() {
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.cols; j++) {
                if (this.grid[i][j]) System.out.print("X");
                else System.out.print(".");
            }
            System.out.println();
        }
        System.out.println();
    }
}
