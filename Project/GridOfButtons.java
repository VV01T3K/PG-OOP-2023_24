import javax.swing.*;
import java.awt.*;
import javax.swing.border.Border;

import java.util.Scanner;

public class GridOfButtons extends JFrame {

    static JTextArea bottomTextArea = new JTextArea("Additional text or content here.");

    public GridOfButtons(int width, int height) {
        setTitle("Grid of Buttons");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout()); // Change layout to BorderLayout

        // Inside the GridOfButtons constructor, before setting up the grid panel

        // 1. Create a JToolBar object
        JToolBar toolBar = new JToolBar();

        // 2. Add buttons or other components to the toolbar
        toolBar.add(new JButton("Button 1"));
        toolBar.add(new JButton("Button 2"));
        toolBar.addSeparator();
        toolBar.add(new JButton("Button 3"));

        // 3. Set the toolbar's floatability
        toolBar.setFloatable(false);

        // 4. Add the toolbar to the frame, specifically to the NORTH region of the
        // BorderLayout
        add(toolBar, BorderLayout.NORTH);

        // Create the grid panel
        JPanel gridPanel = new JPanel(new GridLayout(height, width));
        // Create and add buttons to the grid panel
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                JButton button = new JButton(x + "🔳," + y);
                gridPanel.add(button);
            }
        }

        // Create a border and set it to the grid panel
        Border padding = BorderFactory.createEmptyBorder(10, 10, 10, 10); // Top, left, bottom, right padding
        gridPanel.setBorder(padding);

        // Add grid panel to the center
        add(gridPanel, BorderLayout.CENTER);

        // Inside the GridOfButtons constructor

        // Create the side panel
        JPanel sidePanel = new JPanel();
        sidePanel.setLayout(new BorderLayout());

        // Set preferred and minimum size of the side panel
        Dimension sidePanelSize = new Dimension(200, height * 100); // Assuming each button's height is roughly 100
                                                                    // pixels
        sidePanel.setPreferredSize(sidePanelSize);
        sidePanel.setMinimumSize(new Dimension(100, height * 100)); // Ensure it doesn't get smaller than this

        JTextArea textArea = new JTextArea(
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
        textArea.setWrapStyleWord(true);
        textArea.setLineWrap(true);
        textArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(textArea); // Add scroll pane for text area
        sidePanel.add(scrollPane, BorderLayout.CENTER);

        // Inside the GridOfButtons constructor, after initializing the sidePanel

        // Change the layout of the sidePanel to BoxLayout with vertical alignment
        sidePanel.setLayout(new BoxLayout(sidePanel, BoxLayout.Y_AXIS));

        // Create the bottom side panel
        JPanel bottomSidePanel = new JPanel();
        bottomSidePanel.setLayout(new BorderLayout());
        Dimension bottomPanelSize = new Dimension(200, (height * 100) / 2); // Assuming you want to split the height
                                                                            // evenly
        bottomSidePanel.setPreferredSize(bottomPanelSize);

        // Optionally, add content to the bottom side panel
        bottomTextArea.setWrapStyleWord(true);
        bottomTextArea.setLineWrap(true);
        bottomTextArea.setEditable(false);
        JScrollPane bottomScrollPane = new JScrollPane(bottomTextArea); // Add scroll pane for the bottom text area
        bottomSidePanel.add(bottomScrollPane, BorderLayout.CENTER);

        // Add the bottom side panel to the sidePanel
        sidePanel.add(bottomScrollPane); // Add the bottomScrollPane directly to the sidePanel to align under the first
                                         // scrollPane

        // Adjust the pack() method call if necessary to accommodate the new layout
        pack();

        // Add side panel to the east
        add(sidePanel, BorderLayout.EAST);

        pack(); // Adjusts frame to just fit its subcomponents
        setVisible(true);
    }

    public static void main(String[] args) {
        // Example: create a 5x5 grid of buttons with a side panel
        new GridOfButtons(5, 5);
        int i = 0;
        Scanner scanner = new Scanner(System.in);
        while (true) {
            bottomTextArea.setText("Your 🔳 new text here." + i++);
            System.out.println("Press Enter to continue...");
            String input = scanner.nextLine();
        }
    }
}