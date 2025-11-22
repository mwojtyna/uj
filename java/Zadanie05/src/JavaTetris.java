import java.util.*;

public class JavaTetris implements Tetris {
    /// 1-indexed
    private int rows;
    /// 0-indexed
    private int cols;
    private boolean[][] grid;

    public static void main(String[] args) {
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

        /*{
            JavaTetris tetris = new JavaTetris();
            tetris.cols(11);
            tetris.rows(18);

            tetris.drop(block1);
            tetris.printGrid();
            tetris.drop(block2);
            tetris.printGrid();
        }*/

        /*{
            JavaTetris tetris = new JavaTetris();
            tetris.cols(11);
            tetris.rows(18);

            tetris.optimalDrop(block1);
            tetris.optimalDrop(block1);
            tetris.printGrid();
            tetris.optimalDrop(block1);
            tetris.printGrid();
            System.out.println(tetris.state());
        }*/
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
        dropBlock(positions, this.grid);
    }

    @Override
    public void optimalDrop(Block block) {
        // Get bounds for col
        int leftmost = 0;
        int rightmost = 0;
        for (Vector dv : block.squares()) {
            leftmost = Math.min(leftmost, dv.dCol());
            rightmost = Math.max(rightmost, dv.dCol());
        }

        boolean[][] bestGrid = null;
        int maxDRow = -1;

        for (int dCol = Math.abs(leftmost); dCol < this.cols - rightmost; dCol++) {
            int finalDCol = dCol;
            Block cur = new Block() {
                @Override
                public Position base() {
                    return new Position(finalDCol, block.base().row());
                }

                @Override
                public Set<Vector> squares() {
                    return block.squares();
                }
            };

            boolean[][] simGrid = deepCopy(this.grid);
            int dRow = dropBlock(fromOramusBlock(cur), simGrid);
            if (dRow > maxDRow) {
                maxDRow = dRow;
                bestGrid = simGrid;
            }
        }

        if (bestGrid == null) {
            throw new IllegalStateException("Didn't choose optimal placement");
        }
        this.grid = bestGrid;
    }

    @Override
    public List<Integer> state() {
        List<Integer> res = new ArrayList<>(Collections.nCopies(this.cols, 0));
        for (int row = 0; row < this.rows; row++) {
            for (int col = 0; col < this.cols; col++) {
                if (this.grid[row][col] && res.get(col) == 0) {
                    res.set(col, convertRowCoords(row));
                }
            }
        }

        return res;
    }

    /// @return change in row
    private int dropBlock(List<Position> block, boolean[][] grid) {
        for (int dRow = 0; dRow < this.rows; dRow++) {
            for (Position pos : block) {
                if (pos.row() + dRow + 1 >= this.rows || grid[pos.row() + dRow + 1][pos.col()]) {
                    int rowsErased = placeBlock(block, dRow, grid);
                    return dRow + rowsErased;
                }
            }
        }

        throw new IllegalStateException("Didn't place the block");
    }

    /// @return how many lines where erased
    private int placeBlock(List<Position> block, int dRow, boolean[][] grid) {
        int rowsErased = 0;

        // Update grid
        for (Position pos2 : block) {
            assert !grid[pos2.row() + dRow][pos2.col()];
            grid[pos2.row() + dRow][pos2.col()] = true;
        }

        // Check for row erasing
        for (int row = this.rows - 1; row >= 0; ) {
            boolean line = true;
            for (int col = 0; col < this.cols; col++) {
                if (!grid[row][col]) {
                    line = false;
                    break;
                }
            }

            if (!line) {
                row--;
            } else {
                // Erase row
                for (int col = 0; col < this.cols; col++) {
                    grid[row][col] = false;
                }

                // Move every line down
                for (int row2 = row; row2 >= 1; row2--) {
                    grid[row2] = grid[row2 - 1];
                }
                // Edge case: clear out the top row
                for (int col = 0; col < this.cols; col++) {
                    grid[0][col] = false;
                }

                rowsErased++;
            }
        }

        return rowsErased;
    }

    private List<Position> fromOramusBlock(Block block) {
        List<Position> res = new ArrayList<>(block.squares().size() + 1);

        int baseRow = convertRowCoords(block.base().row());
        int baseCol = block.base().col();

        res.add(new Position(baseCol, baseRow));
        for (Vector dv : block.squares()) {
            res.add(new Position(baseCol + dv.dCol(), baseRow - dv.dRow()));
        }

        return res;
    }

    private int convertRowCoords(int row) {
        return this.rows - row;
    }

    /// Prints grid placing X where there is a block
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

    // https://stackoverflow.com/a/1564856/9854703
    public static boolean[][] deepCopy(boolean[][] original) {
        if (original == null) {
            return null;
        }

        final boolean[][] result = new boolean[original.length][];
        for (int i = 0; i < original.length; i++) {
            result[i] = Arrays.copyOf(original[i], original[i].length);
        }
        return result;
    }
}
