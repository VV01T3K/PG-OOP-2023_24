import javax.swing.*;

import Utils.GUI.GUI;

import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.List;

public class RhombusBoard extends JFrame {

    public RhombusBoard() {
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Rhombus Board");
        RhombusPanel rhombusPanel = new RhombusPanel(5, 5);
        this.setContentPane(rhombusPanel);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        this.pack();
    }

    public class RhombusPanel extends JPanel {
        private int squareSize = 20;
        private int width;
        private int height;
        private GUI gui;
        private List<Polygon> hexagons = new ArrayList<>();

        public RhombusPanel(int width, int height, GUI gui) {
            this.width = width; // Set the width
            this.height = height; // Set the height
            setPreferredSize(new Dimension(squareSize * 22, squareSize * 15));
            addMouseListener(new MouseAdapter() {
                @Override
                public void mouseClicked(MouseEvent e) {
                    super.mouseClicked(e);
                    int hexIndex = 0;
                    for (Polygon hex : hexagons) {
                        if (hex.contains(e.getPoint())) {
                            System.out.println("Hexagon clicked: " + hexIndex);
                            break;
                        }
                        hexIndex++;
                    }
                }
            });
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            hexagons.clear();
            int minDimension = Math.min(getWidth(), getHeight());
            squareSize = (minDimension / Math.max(width, height)) * 2 / 3;

            int xOffset = (getWidth() - (squareSize * width)) / 2;
            int yOffset = (getHeight() - (squareSize * height)) / 2;

            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    int x = (i - j) * squareSize + getWidth() / 2 + xOffset;
                    int y = (i + j) * squareSize / 2 + yOffset;
                    Polygon hex = drawHexagon(g, x - squareSize * 3, y, squareSize, i * width + j);
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
            g2d.setColor(Color.CYAN);
            g2d.fillPolygon(hex);
            g2d.setStroke(new BasicStroke(3));
            g2d.setColor(Color.BLACK);
            g2d.drawPolygon(hex);

            g2d.setColor(Color.BLACK);
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