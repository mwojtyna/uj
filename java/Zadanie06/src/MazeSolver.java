import java.util.*;

public class MazeSolver implements Maze {
    private int rows;
    private int cols;
    private boolean[][] grid;
    private List<Integer> howFar; // col -> value
    private List<Integer> area;   // col -> value
    private final Set<Square> unreachable = new HashSet<>();

    @Override
    public void rows(int rows) {
        this.rows = rows;
        this.grid = new boolean[this.rows][this.cols];
    }

    @Override
    public void cols(int cols) {
        this.cols = cols;
        this.grid = new boolean[this.rows][this.cols];
        this.howFar = new ArrayList<>(Collections.nCopies(this.cols, 0));
        this.area = new ArrayList<>(Collections.nCopies(this.cols, 0));
    }

    @Override
    public void occupiedSquare(Set<Square> squares) {
        for (Square square : squares) {
            this.grid[square.row()][square.col()] = true;
        }

        Set<Square> allVisited = new HashSet<>();
        for (int col = 0; col < this.cols; col++) {
            if (!this.grid[0][col]) {
                Set<Square> visited = bfs(col);
                allVisited.addAll(visited);
            }
        }

        for (int row = 0; row < this.rows; row++) {
            for (int col = 0; col < this.cols; col++) {
                Square cur = new Square(col, row);
                if (!this.grid[row][col] && !allVisited.contains(cur)) {
                    this.unreachable.add(cur);
                }
            }
        }
    }

    @Override
    public List<Integer> howFar() {
        return this.howFar;
    }

    @Override
    public List<Integer> area() {
        return this.area;
    }

    @Override
    public Set<Square> unreachableSquares() {
        return this.unreachable;
    }

    private Set<Square> bfs(int col) {
        Square start = new Square(col, 0);
        Set<Square> visited = new HashSet<>(Collections.singleton(start));
        Queue<Square> queue = new ArrayDeque<>(Collections.singleton(start));
        int furthestRow = 0;

        while (!queue.isEmpty()) {
            Square square = queue.poll();
            furthestRow = Math.max(furthestRow, square.row());

            for (Square nb : square.neighbours()) {
                if ((0 <= nb.row() && nb.row() < this.rows) && (0 <= nb.col() && nb.col() < this.cols) &&
                    !this.grid[nb.row()][nb.col()] && !visited.contains(nb)) {
                    queue.offer(nb);
                    visited.add(nb);
                }
            }
        }

        this.howFar.set(col, furthestRow);
        this.area.set(col, visited.size());
//        System.out.println("furthestRow " + furthestRow);
//        System.out.println("area " + visited.size());
//        printGrid(visited);

        return visited;
    }

    private int convertRow(int row) {
        return this.rows - row - 1;
    }

    private void printGrid(Set<Square> squares) {
        for (int row = 0; row < this.rows; row++) {
            for (int col = 0; col < this.cols; col++) {
                Square cur = new Square(col, convertRow(row));
                if (squares.contains(cur)) {
                    System.out.print("X");
                } else {
                    System.out.print(".");
                }
            }
            System.out.println();
        }
        System.out.println();
    }
}

