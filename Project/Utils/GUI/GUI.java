package Utils.GUI;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.event.*;
import java.awt.*;

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

    private void constructControlPanel() {
        controlPanel.removeAll();
        controlPanel.setLayout(new BoxLayout(controlPanel, BoxLayout.Y_AXIS));
        controlPanel.add(new JLabel("Control Panel"));
        controlPanel.add(new JLabel("World:"));
        controlPanel.add(new JLabel("    Time:" + world.checkTime()));
        controlPanel.add(new JLabel("    Organisms:" + world.getOrganismCount()));

        controlPanel.add(new JLabel("Human:"));
        controlPanel.add(new JLabel("    Next move: Pls give me direction    "));
        controlPanel.add(new JLabel("    🔰 Immortality: Ready to use"));

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
                world.setNewOrganism(type, i, j);
                button.setText(world.getTile(i, j).toString());
                showGameView();
            });
            addOrganismPopup.add(item);
        }

        addOrganismPopup.show(button, x, y);

    }

    private void constructBoardPanel(int width, int height) {
        boardPanel.removeAll(); // Remove all components from the previous board
        boardPanel.setLayout(new ChessBoardLayoutManager()); // Set the layout manager
        // boardPanel.setFont(new Font("DefaultFont", Font.PLAIN, 12));
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                JButton button = new JButton(world.getTile(x, y).toString());
                button.setPreferredSize(new Dimension(50, 50));
                button.setFocusable(false);
                adaptFontSize(button);
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
                button.addComponentListener(new ComponentAdapter() {
                    @Override
                    public void componentResized(ComponentEvent e) {
                        JButton btn = (JButton) e.getComponent();
                        adaptFontSize(btn);
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
            JButton button = buttons.get(p);
            button.setText(world.getTile(p.x, p.y).toString());
        }
    }

    private void adaptFontSize(JButton button) {
        int buttonHeight = button.getHeight();
        int fontSize = Math.max(buttonHeight / 3, 10); // Calculate font size based on button height, minimum size 10
        Font buttonFont = new Font("Sans-Serif", Font.PLAIN, fontSize);
        button.setFont(buttonFont);
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

    public class ChessBoardLayoutManager implements LayoutManager2 {

        private Map<Point, Component> mapComps;

        public ChessBoardLayoutManager() {
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
