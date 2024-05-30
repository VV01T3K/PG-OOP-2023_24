package Utils.GUI;

import Utils.DynamicDirections;

public class SquareKeyBindings extends KeyActionProfile {

    public SquareKeyBindings(GUI gui) {

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
        Runnable moveLeft = () -> {
            if (!gui.getWorld().hasHuman())
                return;
            gui.getWorld().getHuman().setNextMove(DynamicDirections.get("LEFT"));
            gui.getNextRound().setText("<html><div style='text-align: center;'>Next Turn<br/>Move: LEFT</div></html>");
        };
        Runnable moveRight = () -> {
            if (!gui.getWorld().hasHuman())
                return;
            gui.getWorld().getHuman().setNextMove(DynamicDirections.get("RIGHT"));
            gui.getNextRound().setText("<html><div style='text-align: center;'>Next Turn<br/>Move: RIGHT</div></html>");
        };

        addAction("W", moveUp);
        addAction("A", moveLeft);
        addAction("S", moveDown);
        addAction("D", moveRight);

        addAction("VK_UP", moveUp);
        addAction("VK_DOWN", moveDown);
        addAction("VK_LEFT", moveLeft);
        addAction("VK_RIGHT", moveRight);

        addAction("VK_KP_UP", moveUp);
        addAction("VK_KP_DOWN", moveDown);
        addAction("VK_KP_LEFT", moveLeft);
        addAction("VK_KP_RIGHT", moveRight);
    }
}