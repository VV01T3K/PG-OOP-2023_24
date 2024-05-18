import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.BorderFactory;
import javax.swing.JButton;

import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class old_gui implements ActionListener {

    int count = 0;
    JLabel label;

    @Override
    public void actionPerformed(ActionEvent e) {
        System.out.println("Button clicked");
        count++;
        label.setText("Number of clicks: " + count);
    }

    public old_gui() {
        JFrame frame = new JFrame();
        JPanel panel = new JPanel();
        panel.setBorder(BorderFactory.createEmptyBorder(80, 80, 40, 80));
        panel.setLayout(new GridLayout(0, 1));

        // Add a JLabel to the panel
        // JLabel label = new JLabel("🦌🤖🦊👨🐑🐢🐺🌿🍅🌾🍁🍇");
        // panel.add(label);

        JButton button = new JButton("Press me");
        JButton button2 = new JButton("Press me2");
        JLabel label2 = new JLabel("Number of clicks: 0");
        button.addActionListener(this);
        button2.addActionListener(e -> {
            System.out.println("Button clicked");
            count++;
            label2.setText("Number of clicks: " + count);
        });

        panel.add(button);
        label = new JLabel("Number of clicks: 0");
        panel.add(label);
        panel.add(label2);
        panel.add(button2);

        frame.add(panel, BorderLayout.CENTER);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setTitle("Hex World Simulator");
        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        new old_gui();
    }
}