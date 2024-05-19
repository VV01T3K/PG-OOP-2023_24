import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

public class RhombusBoard extends JFrame {

    public RhombusBoard() {
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Rhombus Board");
        this.setContentPane(new RhombusPanel());
        this.pack();
        this.setLocationRelativeTo(null);
        this.setVisible(true);
    }

    private class RhombusPanel extends JPanel {
        private int squareSize = 30; // Initial size of each square
        private final int width = 20; // Number of squares in width
        private final int height = 20; // Number of squares in height

        public RhombusPanel() {
            setLayout(null);
            this.setPreferredSize(new Dimension(squareSize * width * 2, squareSize * height + squareSize));
            initializeButtons();
            addComponentListener(new ComponentAdapter() {
                @Override
                public void componentResized(ComponentEvent e) {
                    adjustButtonSizesAndPositions();
                }
            });
        }

        private void initializeButtons() {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    JButton button = new JButton();
                    this.add(button);
                }
            }
            adjustButtonSizesAndPositions();
        }

        private void adjustButtonSizesAndPositions() {
            int panelWidth = getWidth();
            int panelHeight = getHeight();
            // Example calculation, adjust based on your layout needs
            squareSize = Math.min(panelWidth / (width * 2), panelHeight / (height + 1));
            int count = 0;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    JButton button = (JButton) this.getComponent(count++);
                    int x = (i - j) * squareSize + panelWidth / 2;
                    int y = (i + j) * squareSize / 2;
                    button.setBounds(x, y, squareSize, squareSize);
                    button.setMargin(new Insets(0, 0, 0, 0));
                }
            }
        }
    }

    public static void main(String[] args) {
        new RhombusBoard();
    }
}