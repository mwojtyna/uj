import java.util.*;

public class MazeSolver implements Maze {
    private int rows;
    private int cols;
    private boolean[][] grid;
    private List<Integer> howFar; // col -> value
    private List<Integer> area;   // col -> value
    private final Set<Square> unreachable = new HashSet<>();

    public static void main(String[] args) {
        Set<Square> occupied = new HashSet<>();

        // Rząd 17
        occupied.add(new Square(0, 17));
        occupied.add(new Square(7, 17));
        occupied.add(new Square(10, 17));

        // Rząd 16
        occupied.add(new Square(1, 16));
        occupied.add(new Square(3, 16));
        occupied.add(new Square(5, 16));
        occupied.add(new Square(7, 16));
        occupied.add(new Square(9, 16));

        // Rząd 15
        occupied.add(new Square(3, 15));
        occupied.add(new Square(10, 15));

        // Rząd 14
        occupied.add(new Square(1, 14));
        occupied.add(new Square(2, 14));
        occupied.add(new Square(5, 14));
        occupied.add(new Square(6, 14));
        occupied.add(new Square(7, 14));
        occupied.add(new Square(8, 14));

        // Rząd 13
        occupied.add(new Square(1, 13));
        occupied.add(new Square(3, 13));
        occupied.add(new Square(4, 13));
        occupied.add(new Square(10, 13));

        // Rząd 12
        occupied.add(new Square(2, 12));
        occupied.add(new Square(6, 12));
        occupied.add(new Square(8, 12));

        // Rząd 11
        occupied.add(new Square(4, 11));
        occupied.add(new Square(5, 11));
        occupied.add(new Square(7, 11));
        occupied.add(new Square(9, 11));

        // Rząd 10
        occupied.add(new Square(0, 10));
        occupied.add(new Square(1, 10));
        occupied.add(new Square(2, 10));
        occupied.add(new Square(4, 10));
        occupied.add(new Square(8, 10));

        // Rząd 9
        occupied.add(new Square(3, 9));
        occupied.add(new Square(4, 9));
        occupied.add(new Square(5, 9));
        occupied.add(new Square(8, 9));
        occupied.add(new Square(10, 9));

        // Rząd 8
        occupied.add(new Square(1, 8));
        occupied.add(new Square(3, 8));
        occupied.add(new Square(7, 8));
        occupied.add(new Square(8, 8));

        // Rząd 7
        occupied.add(new Square(5, 7));
        occupied.add(new Square(6, 7));
        occupied.add(new Square(9, 7));

        // Rząd 6
        occupied.add(new Square(0, 6));
        occupied.add(new Square(1, 6));
        occupied.add(new Square(2, 6));
        occupied.add(new Square(5, 6));
        occupied.add(new Square(7, 6));
        occupied.add(new Square(9, 6));

        // Rząd 5
        occupied.add(new Square(3, 5));
        occupied.add(new Square(5, 5));
        occupied.add(new Square(9, 5));

        // Rząd 4
        occupied.add(new Square(1, 4));
        occupied.add(new Square(3, 4));
        occupied.add(new Square(6, 4));
        occupied.add(new Square(8, 4));

        // Rząd 3
        occupied.add(new Square(1, 3));
        occupied.add(new Square(4, 3));
        occupied.add(new Square(6, 3));
        occupied.add(new Square(8, 3));
        occupied.add(new Square(10, 3));

        // Rząd 2
        occupied.add(new Square(2, 2));
        occupied.add(new Square(4, 2));
        occupied.add(new Square(6, 2));
        occupied.add(new Square(8, 2));

        // Rząd 1
        occupied.add(new Square(0, 1));
        occupied.add(new Square(3, 1));
        occupied.add(new Square(6, 1));
        occupied.add(new Square(9, 1));

        // Rząd 0
        occupied.add(new Square(2, 0));
        occupied.add(new Square(5, 0));
        occupied.add(new Square(8, 0));

        {
            MazeSolver mazeSolver = new MazeSolver();
            mazeSolver.rows(18);
            mazeSolver.cols(11);
            mazeSolver.occupiedSquare(occupied);
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

