package Utils.GUI;

import java.util.HashMap;
import java.util.Map;

import javax.swing.*;

import java.awt.event.ActionEvent;

// Step 2: Store Profiles
class ProfileManager {
    private Map<String, KeyActionProfile> profiles = new HashMap<>();
    private KeyActionProfile currentProfile;
    private JPanel contentPane;

    ProfileManager(JFrame window) {
        this.contentPane = (JPanel) window.getContentPane();
        contentPane.setFocusable(true);
    }

    public void addProfile(String name, KeyActionProfile profile) {
        profiles.put(name, profile);
    }

    public void switchProfile(String name) {
        currentProfile = profiles.get(name);
        applyKeyActions();
    }

    private void applyKeyActions() {
        InputMap inputMap = contentPane.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW);
        ActionMap actionMap = contentPane.getActionMap();

        inputMap.clear();
        actionMap.clear();

        currentProfile.getKeyActions().forEach((keyStrokeString, action) -> {
            KeyStroke keyStroke = KeyStroke.getKeyStroke(keyStrokeString);
            if (keyStroke != null) {
                inputMap.put(keyStroke, keyStrokeString);
                actionMap.put(keyStrokeString, new AbstractAction() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        action.run();
                    }
                });
            }
        });
    }

}