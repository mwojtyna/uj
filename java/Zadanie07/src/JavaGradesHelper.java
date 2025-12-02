import java.io.*;
import java.nio.CharBuffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;

public class JavaGradesHelper implements GradesHelper {
    private final List<Student> students = new ArrayList<>();

    public static void main(String[] args) {
        {
            JavaGradesHelper grading = new JavaGradesHelper();
            grading.loadStudents("./src/studenci.txt");
        }
    }

    @Override
    public void loadStudents(String file) {
        try {
            FileReader reader = new FileReader(file);
            while (true) {
                String line = readUntil(reader, ';');
                if (line.isEmpty()) {
                    break;
                }

                String[] parts = line.split(",");
                if (parts.length != 3) {
                    continue;
                }

                this.students.add(new Student(Integer.parseInt(parts[0]), parts[1], parts[2]));
            }
        } catch (IOException ignored) {
        }

        System.out.println(students);
    }

    @Override
    public void loadScoring(String file) throws RangeConflictException, MarkConflictException {

    }

    @Override
    public Map<Integer, String> generateGrades(String data) throws AssessmentImpossible {
        return Map.of();
    }

    private String readUntil(Reader reader, char until) throws IOException {
        int c;
        StringBuilder builder = new StringBuilder();
        while ((c = reader.read()) != -1) {
            if (c == '\n') {
                continue;
            }

            if (c == until) {
                return builder.toString();
            }
            builder.append((char) c);
        }

        return builder.toString();
    }
}

record Student(int id, String name, String lastName) {
}
