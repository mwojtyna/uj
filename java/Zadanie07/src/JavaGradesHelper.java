import java.io.*;
import java.util.*;

public class JavaGradesHelper implements GradesHelper {
    private final int SCORING_COLS = 3;
    private final Map<Student, Integer> studentToId = new HashMap<>();
    private final Map<String, GradeRange> grades = new HashMap<>(); // grade name -> score range

    public static void main(String[] args) {
        {
            JavaGradesHelper grading = new JavaGradesHelper();

            grading.loadStudents("./src/students.txt");
            System.out.println(grading.studentToId);

            try {
                grading.loadScoring("./src/scoring.txt");
            } catch (RangeConflictException | MarkConflictException e) {
                throw new RuntimeException(e);
            }
            System.out.println(grading.grades);
        }
    }

    @Override
    public void loadStudents(String file) {
        try {
            FileReader reader = new FileReader(file);
            String line;
            while (!(line = readUntil(reader, ';')).isEmpty()) {
                String[] parts = line.split("[,;]");
                if (parts.length != 3) {
                    continue;
                }

                int id = Integer.parseInt(parts[0]);
                var student = new Student(parts[1], parts[2]);
                this.studentToId.put(student, id);
            }
        } catch (IOException ignored) {
        }
    }

    @Override
    public void loadScoring(String file) throws RangeConflictException, MarkConflictException {
        try {
            FileReader reader = new FileReader(file);
            String line;
            while (!(line = readUntil(reader, ';', SCORING_COLS)).isEmpty()) {
                String[] parts = line.split(";");
                if (parts.length != 3) {
                    continue;
                }
                this.grades.put(parts[0], new GradeRange(Double.parseDouble(parts[1]), Double.parseDouble(parts[2])));
                // TODO: handle exceptions
            }
        } catch (IOException ignored) {
        }
    }

    @Override
    public Map<Integer, String> generateGrades(String data) throws AssessmentImpossible {
        return Map.of();
    }

    private String readUntil(Reader reader, char until) throws IOException {
        return readUntil(reader, until, 1);
    }

    private String readUntil(Reader reader, char until, int nOccurrences) throws IOException {
        int c;
        int occurrences = 0;
        StringBuilder builder = new StringBuilder();

        while ((c = reader.read()) != -1) {
            if (c == '\n') {
                continue;
            }

            builder.append((char) c);
            if (c == until) {
                if (++occurrences == nOccurrences) {
                    return builder.toString();
                }
            }
        }

        return builder.toString();
    }
}

record Student(String name, String lastName) {
}

record GradeRange(double min, double max) {
}
