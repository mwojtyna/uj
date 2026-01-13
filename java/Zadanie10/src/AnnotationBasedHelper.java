import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.util.Map;

public class AnnotationBasedHelper implements SQLiteHelper {
    private enum SQLType {
        INTEGER,
        REAL,
        TEXT
    }
    private final Map<String, SQLType> typeMap = Map.ofEntries(
        Map.entry("int", SQLType.INTEGER),
        Map.entry("long", SQLType.INTEGER),
        Map.entry("Integer", SQLType.INTEGER),
        Map.entry("Long", SQLType.INTEGER),

        Map.entry("float", SQLType.REAL),
        Map.entry("double", SQLType.REAL),
        Map.entry("Float", SQLType.REAL),
        Map.entry("Double", SQLType.REAL),

        Map.entry("String", SQLType.TEXT)
    );

    @Override
    public String toSQL(Object object, String tableName) {
        StringBuilder builder = new StringBuilder("CREATE TABLE ");
        builder.append(tableName).append(" (");

        Class<?> oc = object.getClass();
        Field[] fields = oc.getFields();

        for (Field field : fields) {
            Annotation sql = field.getAnnotation(SQL.class);
            String fieldTypeName = field.getType().getSimpleName();
            if (sql == null || !this.typeMap.containsKey(fieldTypeName)) {
                continue;
            }

            String sqlType = this.typeMap.get(fieldTypeName).toString();
            builder.append(field.getName()).append(' ').append(sqlType).append(", ");
        }

        builder.delete(builder.length() - 2, builder.length());
        builder.append(");");
        return builder.toString();
    }
}
