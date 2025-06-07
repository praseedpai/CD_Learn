import javax.swing.*;
import java.awt.*;
import java.awt.geom.Line2D;
import java.util.Calendar;

 class Matrix {
    private final double[][] mat;

    public Matrix(double[][] values) {
        this.mat = values;
    }

    public static Matrix identity() {
        return new Matrix(new double[][]{
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        });
    }

    public static Matrix translation(double tx, double ty) {
        return new Matrix(new double[][]{
            {1, 0, tx},
            {0, 1, ty},
            {0, 0, 1}
        });
    }

    public static Matrix scaling(double sx, double sy) {
        return new Matrix(new double[][]{
            {sx, 0, 0},
            {0, sy, 0},
            {0, 0, 1}
        });
    }

    public static Matrix rotation(double theta) {
        double cosT = Math.cos(theta);
        double sinT = Math.sin(theta);
        return new Matrix(new double[][]{
            {cosT, -sinT, 0},
            {sinT, cosT, 0},
            {0, 0, 1}
        });
    }

    public Matrix multiply(Matrix other) {
        double[][] result = new double[3][3];
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    result[i][j] += this.mat[i][k] * other.mat[k][j];
        return new Matrix(result);
    }

    public double[] transformPoint(double x, double y) {
        double[] point = {x, y, 1};
        double[] result = new double[3];

        for (int i = 0; i < 3; i++) {
            result[i] = mat[i][0] * point[0] + mat[i][1] * point[1] + mat[i][2] * point[2];
        }
        return new double[]{result[0], result[1]}; // Return transformed (x, y)
    }
}

 class SwingClock2 extends JPanel {
    private static final int SIZE = 400;
    private static final int CLOCK_RADIUS = 160;

    public SwingClock2() {
        Timer timer = new Timer(1000, e -> repaint()); // Update clock every second
        timer.start();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        // Draw clock face
        g2d.setColor(new Color(175, 238, 238));
        g2d.fillOval(20, 20, SIZE - 40, SIZE - 40);
        g2d.setColor(Color.BLACK);
        g2d.drawOval(20, 20, SIZE - 40, SIZE - 40);

        // Draw numerals using Affine Transformation
        g2d.setFont(new Font("Serif", Font.BOLD, 24));
        for (int i = 1; i <= 12; i++) {
            double angle = Math.toRadians(30 * i);
            Matrix rotation = Matrix.rotation(angle);
            Matrix translation = Matrix.translation(200, 200);
            Matrix transform = translation.multiply(rotation);

            double[] position = transform.transformPoint(CLOCK_RADIUS - 30, 0);
            g2d.drawString(Integer.toString(i), (int) position[0] - 10, (int) position[1] + 10);
        }

        // Get current time
        Calendar now = Calendar.getInstance();
        int hour = now.get(Calendar.HOUR) % 12;
        int minute = now.get(Calendar.MINUTE);
        int second = now.get(Calendar.SECOND);

        // Compute angles for clock hands
        double angleHour = Math.toRadians((hour + minute / 60.0) * 30);
        double angleMinute = Math.toRadians(minute * 6);
        double angleSecond = Math.toRadians(second * 6);

        // Apply matrix-based transformations for clock hands
        drawHand(g2d, angleHour, CLOCK_RADIUS * 0.5, 6, Color.BLACK);
        drawHand(g2d, angleMinute, CLOCK_RADIUS * 0.75, 4, Color.BLUE);
        drawHand(g2d, angleSecond, CLOCK_RADIUS * 0.85, 2, Color.RED);
    }

    private void drawHand(Graphics2D g2d, double angle, double length, int thickness, Color color) {
        g2d.setColor(color);
        g2d.setStroke(new BasicStroke(thickness));

        // Transformation: Scaling, Rotation, Translation
        Matrix scale = Matrix.scaling(length, length);
        Matrix rotation = Matrix.rotation(angle - Math.PI / 2);
        Matrix translation = Matrix.translation(200, 200);
        Matrix transform = translation.multiply(rotation).multiply(scale);

        double[] endpoint = transform.transformPoint(1, 0);
        g2d.draw(new Line2D.Double(200, 200, endpoint[0], endpoint[1]));
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Swing Clock with Affine Transformations");
        SwingClock2 clock = new SwingClock2();
        frame.add(clock);
        frame.setSize(SIZE, SIZE);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}

public class SwingClock extends JPanel {
    private static final int SIZE = 400;
    private static final int CLOCK_RADIUS = 160;
    
    public SwingClock() {
        Timer timer = new Timer(1000, e -> repaint());
        timer.start();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        // Draw clock face
        g2d.setColor(new Color(175, 238, 238));
        g2d.fillOval(20, 20, SIZE - 40, SIZE - 40);

        g2d.setColor(Color.BLACK);
        g2d.drawOval(20, 20, SIZE - 40, SIZE - 40);

        // Draw numerals
        g2d.setFont(new Font("Serif", Font.BOLD, 24));
        for (int i = 1; i <= 12; i++) {
            double angle = Math.toRadians(30 * i);
            int x = (int) (200 + (CLOCK_RADIUS - 30) * Math.cos(angle - Math.PI / 2));
            int y = (int) (200 + (CLOCK_RADIUS - 30) * Math.sin(angle - Math.PI / 2));
            g2d.drawString(Integer.toString(i), x - 10, y + 10);
        }

        // Get current time
        Calendar now = Calendar.getInstance();
        int hour = now.get(Calendar.HOUR) % 12;
        int minute = now.get(Calendar.MINUTE);
        int second = now.get(Calendar.SECOND);

        // Convert time to angles
        double angleHour = Math.toRadians((hour + minute / 60.0) * 30 - 90);
        double angleMinute = Math.toRadians(minute * 6 - 90);
        double angleSecond = Math.toRadians(second * 6 - 90);

        // Draw clock hands
        drawHand(g2d, angleHour, CLOCK_RADIUS * 0.5, 6, Color.BLACK);
        drawHand(g2d, angleMinute, CLOCK_RADIUS * 0.75, 4, Color.BLUE);
        drawHand(g2d, angleSecond, CLOCK_RADIUS * 0.85, 2, Color.RED);
    }

    private void drawHand(Graphics2D g2d, double angle, double length, int thickness, Color color) {
        g2d.setColor(color);
        g2d.setStroke(new BasicStroke(thickness));
        int x = 200, y = 200;
        int xEnd = (int) (x + length * Math.cos(angle));
        int yEnd = (int) (y + length * Math.sin(angle));
        g2d.draw(new Line2D.Double(x, y, xEnd, yEnd));
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Swing Clock by Praseed Pai");
        SwingClock2 clock = new SwingClock2();
        frame.add(clock);
        frame.setSize(SIZE, SIZE);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}


