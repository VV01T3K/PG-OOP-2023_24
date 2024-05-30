package Utils.GUI;

import Utils.DynamicDirections;

public class HexagonalKeyBindings extends KeyActionProfile {
    public HexagonalKeyBindings(GUI gui) {
        addAction("SPACE", () -> gui.getNextRound().doClick());

        Runnable moveUp = () -> {
            if (!gui.getWorld().hasHuman())
                return;
            gui.getWorld().getHuman().setNextMove(DynamicDirections.get("UP"));
            gui.getNextRound().setText("<html><div style='text-align: center;'>Next Turn<br/>Move: UP</div></html>");
        };
        Runnable moveDown = () -> {
            if (!gui.getWorld().hasHuman())
                return;
            gui.getWorld().getHuman().setNextMove(DynamicDirections.get("DOWN"));
            gui.getNextRound().setText("<html><div style='text-align: center;'>Next Turn<br/>Move: DOWN</div></html>");
        };
        Runnable moveTopLeft = () -> {
            if (!gui.getWorld().hasHuman())
                return;
            gui.getWorld().getHuman().setNextMove(DynamicDirections.get("TOP_LEFT"));
            gui.getNextRound()
                    .setText("<html><div style='text-align: center;'>Next Turn<br/>Move: TOP LEFT</div></html>");
        };
        Runnable moveBottomLeft = () -> {
            if (!gui.getWorld().hasHuman())
                return;
            gui.getWorld().getHuman().setNextMove(DynamicDirections.get("BOTTOM_LEFT"));
            gui.getNextRound()
                    .setText("<html><div style='text-align: center;'>Next Turn<br/>Move: BOTTOM LEFT</div></html>");
        };
        Runnable moveTopRight = () -> {
            if (!gui.getWorld().hasHuman())
                return;
            gui.getWorld().getHuman().setNextMove(DynamicDirections.get("TOP_RIGHT"));
            gui.getNextRound()
                    .setText("<html><div style='text-align: center;'>Next Turn<br/>Move: TOP RIGHT</div></html>");
        };
        Runnable moveBottomRight = () -> {
            if (!gui.getWorld().hasHuman())
                return;
            gui.getWorld().getHuman().setNextMove(DynamicDirections.get("BOTTOM_RIGHT"));
            gui.getNextRound()
                    .setText("<html><div style='text-align: center;'>Next Turn<br/>Move: BOTTOM RIGHT</div></html>");
        };

        addAction("Q", moveTopLeft);
        addAction("W", moveUp);
        addAction("E", moveTopRight);
        addAction("A", moveBottomLeft);
        addAction("S", moveDown);
        addAction("D", moveBottomRight);

        addAction("KP_UP", moveUp);
        addAction("KP_DOWN", moveDown);
        addAction("KP_HOME", moveTopLeft);
        addAction("KP_PGUP", moveTopRight);
        addAction("KP_END", moveBottomLeft);
        addAction("KP_PGDN", moveBottomRight);

    }
}