import java.util.List;
import java.util.Set;

public class MazeSolver implements Maze {
    private int rows;
    private int cols;
    private boolean[][] grid;
    private List<Integer> howFar; // col -> value
    private List<Integer> area;   // col -> value

    public static void main(String[] args) {
        {
            MazeSolver mazeSolver = new MazeSolver();
            mazeSolver.rows(18);
            mazeSolver.cols(11);
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
    public void occupiedSquare(Set<Square> squares) {
        for (Square square : squares) {
            this.grid[convertRow(square.row())][square.col()] = true;
        }

        // TODO: BFS
    }

    @Override
    public List<Integer> howFar() {
        return List.of();
    }

    @Override
    public List<Integer> area() {
        return List.of();
    }

    @Override
    public Set<Square> unreachableSquares() {
        return Set.of();
    }

    private int convertRow(int row) {
        return this.rows - row - 1;
    }
}
