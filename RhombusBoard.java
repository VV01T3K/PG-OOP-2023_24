import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.List;

public class RhombusBoard extends JFrame {

    public RhombusBoard() {
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Rhombus Board");
        RhombusPanel rhombusPanel = new RhombusPanel();
        this.setContentPane(rhombusPanel);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        this.setPreferredSize(new Dimension(500, 400));
        this.pack();
    }

    private class RhombusPanel extends JPanel {
        private int squareSize = 30;
        private final int boardSize = 6;
        private List<Polygon> hexagons = new ArrayList<>();

        public RhombusPanel() {
            addMouseListener(new MouseAdapter() {
                @Override
                public void mouseClicked(MouseEvent e) {
                    super.mouseClicked(e);
                    int hexIndex = 0; // Initialize a counter to keep track of the hexagon index
                    for (Polygon hex : hexagons) {
                        if (hex.contains(e.getPoint())) {
                            System.out.println("Hexagon clicked: " + hexIndex); // Print the index of the clicked
                                                                                // hexagon
                            break; // Exit the loop once the clicked hexagon is found
                        }
                        hexIndex++; // Increment the counter for each hexagon checked
                    }
                }
            });
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            hexagons.clear(); // Clear the previous hexagons list
            int minDimension = Math.min(getWidth(), getHeight());
            squareSize = (minDimension / boardSize) * 2 / 3;

            int xOffset = (getWidth() - (squareSize * boardSize)) / 2;
            int yOffset = (getHeight() - (squareSize * boardSize)) / 2;

            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    int x = (i - j) * squareSize + getWidth() / 2 + xOffset;
                    int y = (i + j) * squareSize / 2 + yOffset;
                    Polygon hex = drawHexagon(g, x - squareSize * 3, y, squareSize, i * boardSize + j);
                    hexagons.add(hex);
                }
            }
        }

        private Polygon drawHexagon(Graphics g, int cx, int cy, int r, int hexIndex) {
            int scaledRadius = r / 2;
            Polygon hex = new Polygon();
            for (int i = 0; i < 6; i++) {
                int x = (int) (cx + scaledRadius * Math.cos(i * 2 * Math.PI / 6));
                int y = (int) (cy + scaledRadius * Math.sin(i * 2 * Math.PI / 6));
                hex.addPoint(x, y);
            }
            Graphics2D g2d = (Graphics2D) g;
            // Set color for hexagon fill
            g2d.setColor(Color.CYAN); // Choose your preferred color
            g2d.fillPolygon(hex);
            // Set stroke thickness
            g2d.setStroke(new BasicStroke(3)); // Adjust thickness as needed
            // Set color for hexagon border
            g2d.setColor(Color.BLACK); // Choose your preferred color for the border
            g2d.drawPolygon(hex);

            // Draw the hexagon index or identifier
            g2d.setColor(Color.BLACK); // Ensure the text color contrasts with the hexagon fill color
            // Calculate the position to draw the string so it appears centered
            FontMetrics fm = g2d.getFontMetrics();
            double textWidth = fm.getStringBounds(String.valueOf(hexIndex), g2d).getWidth();
            g2d.drawString(String.valueOf(hexIndex), (int) (cx - textWidth / 2), cy + fm.getAscent() / 2);

            return hex;
        }
    }

    public static void main(String[] args) {
        new RhombusBoard();
    }
}