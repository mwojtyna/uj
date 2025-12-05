import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class JavaGradesHelper implements GradesHelper {
    private final Map<Student, Integer> studentToId = new HashMap<>();
    private final Map<String, GradeRange> grades = new HashMap<>(); // grade name -> score range

    public static void main(String[] args) {
        {
            JavaGradesHelper grading = new JavaGradesHelper();

            grading.loadStudents("./src/students.txt");
            System.out.println(grading.studentToId);

            try {
                grading.loadScoring("./src/scoring.txt");
                System.out.println(grading.grades);
            } catch (RangeConflictException | MarkConflictException e) {
                throw new RuntimeException(e);
            }

            try {
                System.out.println(grading.generateGrades("./src/grades.txt"));
            } catch (AssessmentImpossible e) {
                throw new RuntimeException(e);
            }
        }
    }

    @Override
    public void loadStudents(String file) {
        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(";");
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
        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(";");
                if (parts.length != 3) {
                    continue;
                }

                String gradeName = parts[0];
                GradeRange gradeRange = new GradeRange(Double.parseDouble(parts[1]), Double.parseDouble(parts[2]));

                if (this.grades.containsKey(gradeName) && (this.grades.get(gradeName).min() != gradeRange.min() || this.grades.get(gradeName).max() != gradeRange.max())) {
                    throw new MarkConflictException(gradeName);
                }

                for (var keyValue : this.grades.entrySet()) {
                    String otherName = keyValue.getKey();
                    GradeRange otherRange = keyValue.getValue();
                    if (!gradeName.equals(otherName) && gradeRange.min() <= otherRange.max() && otherRange.min() <= gradeRange.max()) {
                        throw new RangeConflictException();
                    }
                }

                this.grades.put(gradeName, gradeRange);
            }
        } catch (IOException ignored) {
        }
    }

    @Override
    public Map<Integer, String> generateGrades(String data) throws AssessmentImpossible {
        Map<Integer, String> idToGrade = new HashMap<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(data))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(";");
                if (parts.length <= 2) {
                    continue;
                }

                String name = parts[0];
                String lastName = parts[1];
                Student student = new Student(name, lastName);
                if (!this.studentToId.containsKey(student)) {
                    throw new AssessmentImpossible(name, lastName);
                }

                double[] grades = Arrays.stream(Arrays.copyOfRange(parts, 2, parts.length)).mapToDouble(Double::parseDouble).toArray();
                double avg = 0;
                for (double grade : grades) {
                    avg += grade;
                }
                avg /= grades.length;

                int id = this.studentToId.get(student);
                String gradeName = gradeForAverage(avg);
                if (gradeName == null) {
                    throw new AssessmentImpossible(name, lastName);
                }
                idToGrade.put(id, gradeName);
            }
        } catch (IOException ignored) {
        }

        return idToGrade;
    }

    /// @return null when grade not found
    private String gradeForAverage(double avg) {
        for (Map.Entry<String, GradeRange> entry : this.grades.entrySet()) {
            String grade = entry.getKey();
            GradeRange range = entry.getValue();
            if (range.min() <= avg && avg <= range.max()) {
                return grade;
            }
        }
        return null;
    }
}

record Student(String name, String lastName) {
}

record GradeRange(double min, double max) {
}
