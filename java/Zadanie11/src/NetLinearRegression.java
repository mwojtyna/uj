import java.io.*;
import java.net.Socket;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;

public class NetLinearRegression implements NetConnection {
    private final String BEGIN_STRING = "Miło mi Cię powitać!  Z kim rozmawiam: Czlowiek[C] czy Program[P]? Masz 20 sekund na odpowiedź.";
    private final String SEND_HEADER = "Zaczynamy!";
    private final String GIVE_A = "Podaj współczynnik kierunkowy a";
    private final String GIVE_B = "Podaj wyraz wolny b";

    DecimalFormat df = new DecimalFormat();
    DecimalFormatSymbols dotDecimal = new DecimalFormatSymbols();
    DecimalFormatSymbols commaDecimal = new DecimalFormatSymbols();
    BufferedWriter writer;

    public static void main(String[] args) {
        NetLinearRegression reg = new NetLinearRegression();
        reg.connectExecuteClose("172.30.24.12", 9090);
    }

    @Override
    public void connectExecuteClose(String host, int port) {
        this.dotDecimal.setDecimalSeparator('.');
        this.commaDecimal.setDecimalSeparator(',');

        System.out.println("Starting...");

        try (Socket sock = new Socket(host, port)) {
            System.out.println("Connected to " + host + ":" + port);
            BufferedReader reader = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            this.writer = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));

            String line;
            long N = -1;
            long i = 0;

            List<Double> xs = new ArrayList<>();
            List<Double> ys = new ArrayList<>();
            double a = 0;
            double b = 0;

            while ((line = reader.readLine()) != null) {
                System.out.println("SERVER: " + "\"" + line + "\"");

                if (N == -1) {
                    if (line.equals(BEGIN_STRING)) {
                        this.write("P");
                    } else if (line.contains(SEND_HEADER)) {
                        N = Long.parseLong(line.split(":")[1].split(" ")[1]);
                        System.out.println("Read N=" + N);
                    }
                } else {
                    if (i < N) {
                        line = line.trim();
                        String[] numbers = line.split(" +");
                        double x = this.parseNumber(numbers[0]);
                        double y = this.parseNumber(numbers[1]);
                        xs.add(x);
                        ys.add(y);
                        System.out.println("x=" + x + "; y=" + y);
                        i++;
                    }

                    if (line.equals(GIVE_A)) {
                        double[] coeffs = this.calcCoeffs(xs, ys, N);
                        a = coeffs[0];
                        b = coeffs[1];
                        this.write(Double.toString(a));
                    } else if (line.equals(GIVE_B)) {
                        this.write(Double.toString(b));
                    }
                }
            }
        } catch (IOException | ParseException e) {
            throw new RuntimeException(e);
        }
    }

    private double[] calcCoeffs(List<Double> xs, List<Double> ys, long N) {
        assert xs.size() == ys.size() && ys.size() == N;

        double sumXY = 0;
        double sumX = 0;
        double sumY = 0;
        double sumX2 = 0;
        for (int i = 0; i < N; i++) {
            sumXY += xs.get(i) * ys.get(i);
            sumX += xs.get(i);
            sumY += ys.get(i);
            sumX2 += xs.get(i) * xs.get(i);
        }

        double a = (N * sumXY - sumX * sumY) / (N * sumX2 - sumX * sumX);
        double b = (sumY - (a * sumX)) / N;
        return new double[]{a, b};
    }

    private double parseNumber(String s) throws ParseException {
        if (s.contains(".")) {
            this.df.setDecimalFormatSymbols(this.dotDecimal);
            return this.df.parse(s).doubleValue();
        } else if (s.contains(",")) {
            this.df.setDecimalFormatSymbols(this.commaDecimal);
            return this.df.parse(s).doubleValue();
        } else {
            return this.df.parse(s).doubleValue();
        }
    }

    private void write(String s) throws IOException {
        this.writer.write(s + "\n");
        this.writer.flush();
        System.out.println("Wrote '" + s + "\\n" + "'");
    }
}
