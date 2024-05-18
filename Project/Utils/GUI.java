package Utils;

import javax.swing.*;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;

import java.awt.*;

import Simulator.World;

public class GUI {
    World world;

    JFrame window;
    JToolBar toolBar;
    JPanel menuPanel;
    JPanel newGamePanel;
    JPanel cardPanel; // This will hold the menuPanel and newGamePanel

    public GUI(World world) {
        this.world = world;
        window = new JFrame("Wojciech Siwiec s197815 - \"Grids of Life\"");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setSize(800, 600);
        window.setLayout(new BorderLayout());

        cardPanel = new JPanel(new CardLayout());
        constructMenu(); // Initialize menuPanel
        constructNewGamePanel(); // Initialize newGamePanel
        window.add(cardPanel, BorderLayout.CENTER); // Add cardPanel to the window

        constructToolBar();
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
        newGamePanel = new JPanel();
        GridBagLayout layout = new GridBagLayout();
        newGamePanel.setLayout(layout);
        GridBagConstraints gbc = new GridBagConstraints();

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
            System.out.println("Creating new world with width: " + widthField.getText() + ", height: "
                    + heightField.getText() + ", hexagonal: " + isHexagonal);
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
        JButton menuButton = new JButton("Menu");
        menuButton.addActionListener(e -> showMenu());
        toolBar.add(menuButton);
        toolBar.add(new JButton("Pause"));
        toolBar.add(new JButton("Reset"));
        toolBar.setFloatable(false);
        toolBar.setVisible(false);

        window.add(toolBar, BorderLayout.NORTH);
    }

    public void showMenu() {
        CardLayout cl = (CardLayout) (cardPanel.getLayout());
        cl.show(cardPanel, "Menu");
        toolBar.setVisible(false);
        window.setSize(400, 300);
        window.revalidate();
        window.repaint();
    }

    public void showNewGamePanel() {
        CardLayout cl = (CardLayout) (cardPanel.getLayout());
        cl.show(cardPanel, "NewGame");
        toolBar.setVisible(true);
        window.revalidate();
        window.repaint();
    }

    private void constructMenu() {
        menuPanel = new JPanel();
        JButton continueButton = new JButton("Continue the game");
        JButton startButton = new JButton("Start new game");
        JButton loadButton = new JButton("Load game");
        JButton exitButton = new JButton("Exit");

        startButton.addActionListener(e -> {
            showNewGamePanel(); // Use showNewGamePanel to switch views
        });

        exitButton.addActionListener(e -> System.exit(0));

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
    }
}