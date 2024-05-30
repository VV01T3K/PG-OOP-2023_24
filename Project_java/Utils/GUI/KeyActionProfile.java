package Utils.GUI;

import java.util.HashMap;
import java.util.Map;

public class KeyActionProfile {
    private Map<String, Runnable> keyActions = new HashMap<>();

    public Map<String, Runnable> getKeyActions() {
        return keyActions;
    }

    public void addAction(String key, Runnable action) {
        keyActions.put(key, action);
    }

    public Runnable getAction(String key) {
        return keyActions.get(key);
    }
}