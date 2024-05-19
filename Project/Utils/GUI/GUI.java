package Utils.GUI;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.event.*;
import java.awt.*;
import java.awt.image.BufferedImage;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.List;

import Simulator.World;
import Simulator.Organisms.Organism.Type;

public class GUI {
    World world;

    private JFrame window;
    private JToolBar toolBar;
    private JPanel cardPanel;
    private JPanel boardPanel;
    private JButton saveButton;
    private JPopupMenu addOrganismPopup;
    private JPanel logPanel;
    private JSplitPane gameView;
    private JButton continueButton;
    private JPanel controlPanel;
    private Map<Point, JButton> buttons = new HashMap<>();

    public GUI(World world) {
        this.world = world;
        boardPanel = new JPanel();
        logPanel = new JPanel();
        controlPanel = new JPanel();

        window = new JFrame("Wojciech Siwiec s197815 - \"Grids of Life\"");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        // window.setResizable(false);
        window.setLayout(new BorderLayout());

        cardPanel = new JPanel(new CardLayout());
        constructMenu(); // Initialize menuPanel
        constructToolBar();
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        constructControlPanel();
        setDefaultFontSize(12);
        constructNewGamePanel(); // Initialize newGamePanel
        constructGameView();
        window.add(cardPanel, BorderLayout.CENTER); // Add cardPanel to the window
        setupKeyBindings();

        window.pack();
    }

    private void setDefaultFontSize(int size) {
        // Get all UI keys from UIManager
        for (Object key : UIManager.getLookAndFeelDefaults().keySet()) {
            if (key != null && key.toString().endsWith(".font")) {
                Font font = UIManager.getDefaults().getFont(key);
                if (font != null) {
                    // Set the new font size
                    font = font.deriveFont((float) size);
                    UIManager.put(key, font);
                }
            }
        }
    }

    private JButton createButton(String htmlText, Color background, Color text) {
        JButton button = new JButton(htmlText);
        button.setFocusable(false);
        button.setOpaque(true);
        button.setContentAreaFilled(true);
        button.setBorderPainted(false);
        button.setBackground(background);
        button.setForeground(text);
        button.setSize(button.getPreferredSize());
        button.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                button.setBackground(button.getBackground().darker());
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                button.setBackground(background);
            }
        });
        return button;
    }

    private void constructControlPanel() {
        controlPanel.removeAll();
        controlPanel.setLayout(new BoxLayout(controlPanel, BoxLayout.Y_AXIS));
        controlPanel.add(new JLabel("Control Panel"));
        controlPanel.add(new JLabel("World:"));
        controlPanel.add(new JLabel("    Time:" + world.checkTime()));
        controlPanel.add(new JLabel("    Organisms:" + world.getOrganismCount()));

        controlPanel.add(new JLabel("Human:"));
        controlPanel.add(new JLabel("    Strength: 10    "));
        JButton useImmortality = createButton(
                "<html><div style='text-align: center;'>🔰 Immortality <br/>"
                        + (world.hasHuman() ? world.getHuman().getAbilityInfo() : "")
                        + "</div></html>",
                Color.WHITE, Color.BLACK); // Assuming default colors are White for foreground and Black for background
        useImmortality.addActionListener(e -> {
            world.getHuman().toggleImmortality();
            useImmortality
                    .setText("<html><div style='text-align: center;'>🔰 Immortality<br/>"
                            + world.getHuman().getAbilityInfo() + "</div></html>");

        });

        JButton nextRound = createButton(
                "<html><div style='text-align: center;'>Next turn<br/><br/></div></html>",
                Color.GREEN, Color.BLACK);
        nextRound.addActionListener(e -> {
            nextRound
                    .setText(
                            "<html><div style='text-align: center;'>Give directions to human<br/>NO DIRECTIONS</div></html>");
            world.simulate();
        });
        controlPanel.add(useImmortality);
        controlPanel.add(nextRound);

        controlPanel.revalidate();
        controlPanel.repaint();

    }

    private void setupKeyBindings() {
        JPanel contentPane = (JPanel) window.getContentPane();
        InputMap inputMap = contentPane.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW);
        ActionMap actionMap = contentPane.getActionMap();

        inputMap.put(KeyStroke.getKeyStroke(KeyEvent.VK_SPACE, 0), "SPACE");
        actionMap.put("SPACE", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                world.simulate();
                updateGameView();
            }
        });

        contentPane.setFocusable(true);
    }

    public void constructGameView() {
        // Step 1: Initialize gameView
        gameView = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
        gameView.setOneTouchExpandable(false); // Users cannot adjust the split
        gameView.setEnabled(false); // Disable the split pane to prevent resizing

        // Step 2: Configure rightSplitPane
        JSplitPane rightSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT);
        rightSplitPane.setOneTouchExpandable(false);
        rightSplitPane.setEnabled(false); // Disable the split pane to prevent resizing

        // Step 3: Add components
        rightSplitPane.setTopComponent(logPanel);
        rightSplitPane.setBottomComponent(controlPanel);
        gameView.setLeftComponent(boardPanel);
        gameView.setRightComponent(rightSplitPane);

        // Adjusting the initial divider location to prioritize left component's space
        gameView.setResizeWeight(1.0);
        rightSplitPane.setResizeWeight(1.0);

        // Step 5: Add gameView to cardPanel instead of directly to window
        cardPanel.add(gameView, "GameView");
    }

    public void updateGameView() {
        updateBoardPanel();
        showGameView();
    }

    private void showGameView() {
        saveButton.setVisible(true);
        constructGameView(); // Ensure gameView is constructed with the new board
        constructControlPanel();
        updateLogPanel();
        CardLayout cl = (CardLayout) (cardPanel.getLayout());
        cl.show(cardPanel, "GameView");
        toolBar.setVisible(true);
        window.revalidate();
        window.repaint();
    }

    public void updateLogPanel() {
        logPanel.removeAll();
        logPanel.setLayout(new BoxLayout(logPanel, BoxLayout.Y_AXIS));
        for (String log : world.getLogs()) {
            JLabel label = new JLabel(log);
            logPanel.add(label);
        }
        logPanel.revalidate();
        logPanel.repaint();
    }

    private void useAddOrganismPopup(int x, int y, JButton button, int i, int j) {
        addOrganismPopup = new JPopupMenu();
        if (button.getText().equals(Type.HUMAN.getSymbol()))
            return;

        for (Type type : Type.values()) {
            if (type == Type.HUMAN)
                continue;
            JMenuItem item = new JMenuItem(type.getSymbol() + " - " + type.name());
            item.addActionListener(e -> {
                world.setNewOrganism(type, j, i);
                ((ResizableIconButton) button).setImageIcon(createIconFromText(world.getTile(j, i).toString()));
                showGameView();
            });
            addOrganismPopup.add(item);
        }

        addOrganismPopup.show(button, x, y);

    }

    public class ResizableIconButton extends JButton {
        private Image originalIconImage;

        public ResizableIconButton(Icon icon) {
            super(icon);
            setIcon(null);
            if (icon instanceof ImageIcon) {
                originalIconImage = ((ImageIcon) icon).getImage();
            }
            this.setPreferredSize(new Dimension(50, 50)); // Match image size or adjust as needed
            this.setFocusable(false);
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            if (originalIconImage != null) {
                Image resizedImage = originalIconImage.getScaledInstance(getWidth(), getHeight(), Image.SCALE_SMOOTH);
                g.drawImage(resizedImage, 0, 0, null);
            }
        }

        public void setImageIcon(Icon newIcon) {
            if (newIcon instanceof ImageIcon) {
                originalIconImage = ((ImageIcon) newIcon).getImage();
                repaint(); // Refresh the button to display the new icon
            }
        }
    }

    private ImageIcon createIconFromText(String text) {
        // Step 1: Create an image (for example, 100x50 pixels)
        BufferedImage image = new BufferedImage(100, 100, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2d = image.createGraphics();

        // Step 2: Customize graphics (optional)
        g2d.setFont(new Font("Sans-serif", Font.BOLD, 60)); // Set font here
        g2d.setColor(Color.BLACK); // Set font color here
        FontMetrics fm = g2d.getFontMetrics();
        int x = (image.getWidth() - fm.stringWidth(text)) / 2;
        int y = ((image.getHeight() - fm.getHeight()) / 2) + fm.getAscent();

        // Draw the text onto the image
        g2d.drawString(text, x, y);
        g2d.dispose();

        // Step 3: Convert the image to an ImageIcon
        return new ImageIcon(image);
    }

    private void constructBoardPanel(int width, int height) {
        boardPanel.removeAll(); // Remove all components from the previous board
        boardPanel.setLayout(new GridBoardLayoutManager()); // Set the layout manager
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                JButton button = new ResizableIconButton(createIconFromText(world.getTile(x, y).toString()));
                final int fi = y;
                final int fj = x;
                button.addMouseListener(new MouseAdapter() {
                    @Override
                    public void mouseClicked(MouseEvent e) {
                        int x = e.getX();
                        int y = e.getY();
                        useAddOrganismPopup(x, y, button, fi, fj);
                    }
                });
                buttons.put(new Point(x, y), button);
                boardPanel.add(button, new Point(x, y));
            }
        }

        boardPanel.revalidate(); // Revalidate the panel to apply changes
        boardPanel.repaint(); // Repaint to display the new buttons
    }

    private void updateBoardPanel() {
        for (Point p : buttons.keySet()) {
            ResizableIconButton button = (ResizableIconButton) buttons.get(p);
            button.setImageIcon(createIconFromText(world.getTile(p.x, p.y).toString()));
        }
    }

    private void addValidationListener(JTextField field) {
        field.getDocument().addDocumentListener(new DocumentListener() {
            public void changedUpdate(DocumentEvent e) {
                verifyInput(field);
            }

            public void removeUpdate(DocumentEvent e) {
            }

            public void insertUpdate(DocumentEvent e) {
                verifyInput(field);
            }
        });
    }

    private void verifyInput(JTextField field) {
        SwingUtilities.invokeLater(() -> {
            try {
                int value = Integer.parseInt(field.getText());
                if (value <= 0) {
                    JOptionPane.showMessageDialog(window, "Value must be greater than 0", "Error",
                            JOptionPane.ERROR_MESSAGE);
                    field.setText(""); // Reset the input field
                } else if (value > 40) {
                    JOptionPane.showMessageDialog(window, "Value must be less than 40", "Error",
                            JOptionPane.ERROR_MESSAGE);
                    field.setText(""); // Reset the input field
                }
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(window, "Please enter a valid number", "Error",
                        JOptionPane.ERROR_MESSAGE);
                field.setText(""); // Reset the input field
            }
        });
    }

    private void constructNewGamePanel() {
        JPanel newGamePanel = new JPanel();
        GridBagLayout layout = new GridBagLayout();
        newGamePanel.setLayout(layout);
        GridBagConstraints gbc = new GridBagConstraints();

        // set preferred size for the newGamePanel
        newGamePanel.setPreferredSize(new Dimension(300, 200));

        gbc.insets = new Insets(5, 5, 5, 5); // Margin between components
        gbc.anchor = GridBagConstraints.WEST; // Align components to the left

        JLabel widthLabel = new JLabel("Width:");
        JTextField widthField = new JTextField(10); // Specify columns to control width
        JLabel heightLabel = new JLabel("Height:");
        JTextField heightField = new JTextField(10); // Specify columns to control width
        JLabel worldType = new JLabel("World type:");
        JComboBox<String> worldTypeComboBox = new JComboBox<>(new String[] { "Square", "Hexagonal" });
        JButton startButton = new JButton("Start");

        addValidationListener(widthField);
        addValidationListener(heightField);

        startButton.addActionListener(e -> {
            if (widthField.getText().isEmpty() || heightField.getText().isEmpty()) {
                JOptionPane.showMessageDialog(window, "Please enter valid values for width and height", "Error",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }
            boolean isHexagonal = worldTypeComboBox.getSelectedItem().equals("Hexagonal");
            int newWidth = Integer.parseInt(widthField.getText());
            int newHeight = Integer.parseInt(heightField.getText());
            world = new World(newWidth, newHeight, isHexagonal);
            world.populateWorld();
            world.setHuman(world.findHuman());

            constructBoardPanel(newWidth, newHeight);
            showGameView(); // Show gameView instead of showBoardPanel
            window.pack();
        });

        // Add components with GridBagConstraints
        gbc.gridx = 0;
        gbc.gridy = 0;
        newGamePanel.add(widthLabel, gbc);
        gbc.gridx = 1;
        gbc.gridy = 0;
        newGamePanel.add(widthField, gbc);
        gbc.gridx = 0;
        gbc.gridy = 1;
        newGamePanel.add(heightLabel, gbc);
        gbc.gridx = 1;
        gbc.gridy = 1;
        newGamePanel.add(heightField, gbc);
        gbc.gridx = 0;
        gbc.gridy = 2;
        newGamePanel.add(worldType, gbc);
        gbc.gridx = 1;
        gbc.gridy = 2;
        newGamePanel.add(worldTypeComboBox, gbc);
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.gridwidth = 2; // Make startButton span two columns
        gbc.anchor = GridBagConstraints.CENTER; // Center the start button
        newGamePanel.add(startButton, gbc);

        cardPanel.add(newGamePanel, "NewGame"); // Add newGamePanel to cardPanel
    }

    private void constructToolBar() {
        toolBar = new JToolBar();
        toolBar.setFocusable(false);
        JButton menuButton = new JButton("Menu");
        menuButton.addActionListener(e -> {
            saveButton.setVisible(false);
            showMenu();
        });
        toolBar.add(menuButton);
        saveButton = new JButton("Save");
        saveButton.setVisible(false);
        saveButton.addActionListener(e -> {
        });
        toolBar.add(saveButton);
        toolBar.setFloatable(false);
        toolBar.setVisible(false);

        window.add(toolBar, BorderLayout.NORTH);
    }

    private void showMenu() {
        CardLayout cl = (CardLayout) (cardPanel.getLayout());
        cl.show(cardPanel, "Menu");
        toolBar.setVisible(false);

        if (world.checkTime() > 0)
            continueButton.setVisible(true);
        else
            continueButton.setVisible(false);

        window.revalidate();
        window.repaint();
    }

    private void showNewGamePanel() {
        CardLayout cl = (CardLayout) (cardPanel.getLayout());
        cl.show(cardPanel, "NewGame");
        toolBar.setVisible(true);
        window.revalidate();
        window.repaint();
        window.pack();
    }

    private void constructMenu() {
        JPanel menuPanel = new JPanel();
        continueButton = new JButton("Continue the game");
        JButton startButton = new JButton("Start new game");
        JButton loadButton = new JButton("Load game");
        JButton exitButton = new JButton("Exit");

        startButton.addActionListener(e -> {
            showNewGamePanel(); // Use showNewGamePanel to switch views
        });

        exitButton.addActionListener(e -> System.exit(0));

        continueButton.addActionListener(e -> {
            showGameView();
        });

        continueButton.setBackground(Color.LIGHT_GRAY);
        continueButton.setVisible(false);
        startButton.setBackground(Color.LIGHT_GRAY);
        loadButton.setBackground(Color.LIGHT_GRAY);
        exitButton.setBackground(Color.RED);

        continueButton.setForeground(Color.BLACK);
        startButton.setForeground(Color.BLACK);
        loadButton.setForeground(Color.BLACK);
        exitButton.setForeground(Color.WHITE);

        continueButton.setFont(new Font("Arial", Font.BOLD, 14));
        startButton.setFont(new Font("Arial", Font.BOLD, 14));
        loadButton.setFont(new Font("Arial", Font.BOLD, 14));
        exitButton.setFont(new Font("Arial", Font.BOLD, 14));

        menuPanel.setLayout(new BoxLayout(menuPanel, BoxLayout.Y_AXIS));
        menuPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        // Add buttons to menuPanel
        menuPanel.add(continueButton);
        menuPanel.add(Box.createRigidArea(new Dimension(0, 5)));
        menuPanel.add(startButton);
        menuPanel.add(Box.createRigidArea(new Dimension(0, 5)));
        menuPanel.add(loadButton);
        menuPanel.add(Box.createRigidArea(new Dimension(0, 5)));
        menuPanel.add(exitButton);

        cardPanel.add(menuPanel, "Menu"); // Add menuPanel to cardPanel
    }

    public void run() {
        window.setVisible(true);
        showMenu();
    }

    public class GridBoardLayoutManager implements LayoutManager2 {

        private Map<Point, Component> mapComps;

        public GridBoardLayoutManager() {
            mapComps = new HashMap<>(25);
        }

        @Override
        public void addLayoutComponent(Component comp, Object constraints) {
            if (constraints instanceof Point) {

                mapComps.put((Point) constraints, comp);

            } else {

                throw new IllegalArgumentException("ChessBoard constraints must be a Point");

            }
        }

        @Override
        public Dimension maximumLayoutSize(Container target) {
            return preferredLayoutSize(target);
        }

        @Override
        public float getLayoutAlignmentX(Container target) {
            return 0.5f;
        }

        @Override
        public float getLayoutAlignmentY(Container target) {
            return 0.5f;
        }

        @Override
        public void invalidateLayout(Container target) {
        }

        @Override
        public void addLayoutComponent(String name, Component comp) {
        }

        @Override
        public void removeLayoutComponent(Component comp) {
            Point[] keys = mapComps.keySet().toArray(new Point[mapComps.size()]);
            for (Point p : keys) {
                if (mapComps.get(p).equals(comp)) {
                    mapComps.remove(p);
                    break;
                }
            }
        }

        @Override
        public Dimension preferredLayoutSize(Container parent) {
            return new CellGrid(mapComps).getPreferredSize();
        }

        @Override
        public Dimension minimumLayoutSize(Container parent) {
            return preferredLayoutSize(parent);
        }

        @Override
        public void layoutContainer(Container parent) {
            int width = parent.getWidth();
            int height = parent.getHeight();

            int gridSize = Math.min(width, height);

            CellGrid grid = new CellGrid(mapComps);
            int rowCount = grid.getRowCount();
            int columnCount = grid.getColumnCount();

            int cellSize = gridSize / Math.max(rowCount, columnCount);

            int xOffset = (width - (cellSize * columnCount)) / 2;
            int yOffset = (height - (cellSize * rowCount)) / 2;

            Map<Integer, List<CellGrid.Cell>> cellRows = grid.getCellRows();
            for (Integer row : cellRows.keySet()) {
                List<CellGrid.Cell> rows = cellRows.get(row);
                for (CellGrid.Cell cell : rows) {
                    Point p = cell.getPoint();
                    Component comp = cell.getComponent();

                    int x = xOffset + (p.x * cellSize);
                    int y = yOffset + (p.y * cellSize);

                    comp.setLocation(x, y);
                    comp.setSize(cellSize, cellSize);

                }
            }

        }

        public class CellGrid {

            private Dimension prefSize;
            private int cellWidth;
            private int cellHeight;

            private Map<Integer, List<Cell>> mapRows;
            private Map<Integer, List<Cell>> mapCols;

            public CellGrid(Map<Point, Component> mapComps) {
                mapRows = new HashMap<>(25);
                mapCols = new HashMap<>(25);
                for (Point p : mapComps.keySet()) {
                    int row = p.y;
                    int col = p.x;
                    List<Cell> rows = mapRows.get(row);
                    List<Cell> cols = mapCols.get(col);
                    if (rows == null) {
                        rows = new ArrayList<>(25);
                        mapRows.put(row, rows);
                    }
                    if (cols == null) {
                        cols = new ArrayList<>(25);
                        mapCols.put(col, cols);
                    }
                    Cell cell = new Cell(p, mapComps.get(p));
                    rows.add(cell);
                    cols.add(cell);
                }

                int rowCount = mapRows.size();
                int colCount = mapCols.size();

                cellWidth = 0;
                cellHeight = 0;

                for (List<Cell> comps : mapRows.values()) {
                    for (Cell cell : comps) {
                        Component comp = cell.getComponent();
                        cellWidth = Math.max(cellWidth, comp.getPreferredSize().width);
                        cellHeight = Math.max(cellHeight, comp.getPreferredSize().height);
                    }
                }

                int cellSize = Math.max(cellHeight, cellWidth);

                prefSize = new Dimension(cellSize * colCount, cellSize * rowCount);
            }

            public int getRowCount() {
                return getCellRows().size();
            }

            public int getColumnCount() {
                return getCellColumns().size();
            }

            public Map<Integer, List<Cell>> getCellColumns() {
                return mapCols;
            }

            public Map<Integer, List<Cell>> getCellRows() {
                return mapRows;
            }

            public Dimension getPreferredSize() {
                return prefSize;
            }

            public int getCellHeight() {
                return cellHeight;
            }

            public int getCellWidth() {
                return cellWidth;
            }

            public class Cell {

                private Point point;
                private Component component;

                public Cell(Point p, Component comp) {
                    this.point = p;
                    this.component = comp;
                }

                public Point getPoint() {
                    return point;
                }

                public Component getComponent() {
                    return component;
                }

            }

        }
    }
}
