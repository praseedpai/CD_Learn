import javax.swing.*;
import java.awt.*;

 class Complex {
    private final double real;
    private final double imaginary;

    public Complex(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public double getReal() {
        return real;
    }

    public double getImaginary() {
        return imaginary;
    }

    public Complex add(Complex other) {
        return new Complex(this.real + other.real, this.imaginary + other.imaginary);
    }

    public Complex multiply(Complex other) {
        double realPart = this.real * other.real - this.imaginary * other.imaginary;
        double imaginaryPart = this.real * other.imaginary + this.imaginary * other.real;
        return new Complex(realPart, imaginaryPart);
    }

    public double modulusSquared() {
        return this.real * this.real + this.imaginary * this.imaginary;
    }
}


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
        return new double[]{result[0], result[1]}; // Return transformed (x,y)
    }
}



class MandelbrotRenderer extends JPanel {
    private static final int WIDTH = 800, HEIGHT = 800;
    private static final int MAX_ITER = 500;
    private static final double ZOOM = 250;

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                double real = (x - WIDTH / 2) / ZOOM;
                double imaginary = (y - HEIGHT / 2) / ZOOM;
                Complex c = new Complex(real, imaginary);
                int iter = mandelbrotIterations(c);

                // Map iteration count to a color gradient
                float hue = iter / (float) MAX_ITER;
                Color color = Color.getHSBColor(hue, 1, iter > 0 ? 1 : 0); 
                g.setColor(color);
                g.drawRect(x, y, 1, 1);
            }
        }
    }

    private int mandelbrotIterations(Complex c) {
        Complex z = new Complex(0, 0);
        int iterations = 0;
        while (iterations < MAX_ITER && z.modulusSquared() < 4) {
            z = z.multiply(z).add(c);
            iterations++;
        }
        return iterations;
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Mandelbrot Set - Colored");
        MandelbrotRenderer panel = new MandelbrotRenderer();
        frame.add(panel);
        frame.setSize(WIDTH, HEIGHT);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}


public class MandelBrotSet extends JPanel {
    private static final int WIDTH = 800, HEIGHT = 800;
    private static final int MAX_ITER = 500;
    private static final double ZOOM = 250;

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                double real = (x - WIDTH / 2) / ZOOM;
                double imaginary = (y - HEIGHT / 2) / ZOOM;
                Complex c = new Complex(real, imaginary);
                int iter = mandelbrotIterations(c);

                // Color mapping based on iterations
                g.setColor(new Color(iter % 256, iter % 256, iter % 256));
                g.drawRect(x, y, 1, 1);
            }
        }
    }

    private int mandelbrotIterations(Complex c) {
        Complex z = new Complex(0, 0);
        int iterations = 0;
        while (iterations < MAX_ITER && z.modulusSquared() < 4) {
            z = z.multiply(z).add(c);
            iterations++;
        }
        return iterations;
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Mandelbrot Set");
        MandelBrotSet panel = new MandelBrotSet();
        frame.add(panel);
        frame.setSize(WIDTH, HEIGHT);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}




 class MandelbrotRenderer2 extends JPanel {
    private static final int WIDTH = 800, HEIGHT = 800;
    private static final int MAX_ITER = 500;
    private static final double ZOOM = 250;

    private final Matrix transformation;

    public MandelbrotRenderer2() {
        // Define transformation: scale and translate viewport
        Matrix scale = Matrix.scaling(1.0 / ZOOM, 1.0 / ZOOM);
        Matrix translate = Matrix.translation(-WIDTH / 2.0, -HEIGHT / 2.0);
        transformation = scale.multiply(translate);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                // Transform pixel coordinates to complex plane
                double[] transformed = transformation.transformPoint(x, y);
                Complex c = new Complex(transformed[0], transformed[1]);
                int iter = mandelbrotIterations(c);

                // Color mapping
                float hue = iter / (float) MAX_ITER;
                g.setColor(Color.getHSBColor(hue, 1, iter > 0 ? 1 : 0));
                g.drawRect(x, y, 1, 1);
            }
        }
    }

    private int mandelbrotIterations(Complex c) {
        Complex z = new Complex(0, 0);
        int iterations = 0;
        while (iterations < MAX_ITER && z.modulusSquared() < 4) {
            z = z.multiply(z).add(c);
            iterations++;
        }
        return iterations;
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Mandelbrot Set with Matrix Transformations");
        MandelbrotRenderer2 panel = new MandelbrotRenderer2();
        frame.add(panel);
        frame.setSize(WIDTH, HEIGHT);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}

