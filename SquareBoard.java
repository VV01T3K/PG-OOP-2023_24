import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.Polygon;

public class SquareBoard {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Rotated Square Board with Hexagons");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        RotatedPanel boardPanel = new RotatedPanel(); // Use our custom rotated panel
        boardPanel.setBackground(Color.WHITE);
        frame.add(boardPanel);
        frame.pack(); // Adjust frame size based on the preferred size of the panel

        frame.setLocationRelativeTo(null); // Center the frame
        frame.setVisible(true);
    }
}

class RotatedPanel extends JPanel {
    private int boardSize = 8; // 8x8 board
    private int cellSize = 50; // Each cell is 50x50 pixels
    private int rowSpacing = (int) (cellSize * 1.2); // Reduced spacing between rows
    private int colSpacing = (int) (cellSize * 1.2); // Reduced spacing between columns

    public RotatedPanel() {
        // Calculate the diagonal length of the board to set the preferred size
        double diagonalLength = Math.sqrt(2) * boardSize * cellSize;
        int panelSize = (int) Math.ceil(diagonalLength);
        setPreferredSize(new java.awt.Dimension(panelSize, panelSize));
        setBackground(Color.WHITE);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g.create();

        // Calculate the center of the panel for rotation
        int centerX = getWidth() / 2;
        int centerY = getHeight() / 2;

        // Rotate around the panel center
        AffineTransform transform = AffineTransform.getRotateInstance(Math.toRadians(45), centerX, centerY);
        g2d.setTransform(transform);

        // Adjust starting position to keep the board centered after rotation and
        // slightly to the right
        int offset = colSpacing + cellSize; // Adjust this value as needed to shift to the right
        int startX = (int) (centerX - (boardSize * cellSize / 2)) + offset;
        int startY = (int) (centerY - (boardSize * cellSize / 2));

        // Draw the board and cells
        for (int row = 0; row < boardSize; row++) {
            for (int col = 0; col < boardSize; col++) {
                g2d.setColor((row + col) % 2 == 0 ? Color.BLACK : Color.WHITE);
                int x = startX + col * colSpacing; // Use colSpacing for horizontal position
                int y = startY + row * rowSpacing; // Use rowSpacing for vertical position
                g2d.fillRect(x, y, cellSize, cellSize);

                // Draw hexagon inside the square
                drawHexagon(g2d, x + cellSize / 2, y + cellSize / 2, cellSize / 3);
            }
        }

        g2d.dispose(); // Clean up
    }

    private void drawHexagon(Graphics2D g2d, int cx, int cy, int r) {
        // Increase the radius to make the hexagon bigger
        int scaledRadius = r * 2;

        Polygon hex = new Polygon();
        for (int i = 0; i < 6; i++) {
            int x = (int) (cx + scaledRadius * Math.cos(i * 2 * Math.PI / 6));
            int y = (int) (cy + scaledRadius * Math.sin(i * 2 * Math.PI / 6));
            hex.addPoint(x, y);
        }
        g2d.setColor(Color.RED); // Set hexagon color

        // Save the original transform
        AffineTransform originalTransform = g2d.getTransform();

        // Create a rotation transform for 30 degrees around the hexagon's center
        AffineTransform rotateTransform = AffineTransform.getRotateInstance(Math.toRadians(15.5), cx, cy);
        g2d.transform(rotateTransform);

        // Fill the hexagon with the specified color
        g2d.fillPolygon(hex);

        // Reset to the original transform to not affect subsequent drawings
        g2d.setTransform(originalTransform);
    }
}



addMouseListener(new MouseAdapter() {
                @Override
                public void mouseClicked(MouseEvent e) {
                    super.mouseClicked(e);
                    for (Polygon hex : hexagons) {
                        if (hex.contains(e.getPoint())) {
                            clickedHexagon = hex;
                            clickedHexagon.fillPolygon(Color.RED);
                            repaint();
                            break;
                        }
                    }
                }
            });

            addMouseMotionListener(new MouseAdapter() {
                @Override
                public void mouseMoved(MouseEvent e) {
                    super.mouseMoved(e);
                    hoveredHexagon = null;
                    for (Polygon hex : hexagons) {
                        if (hex.contains(e.getPoint())) {
                            hoveredHexagon = hex;
                            repaint();
                            break;
                        }
                    }
                }
            });