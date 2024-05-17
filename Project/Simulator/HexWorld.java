package Simulator;

import java.util.ArrayList;

import Utils.DynamicDirections;

public class HexWorld extends World {

    public HexWorld(int width, int height) {

        DynamicDirections.clear();

        DynamicDirections.addInstance("UP");
        DynamicDirections.addInstance("RIGHT");
        DynamicDirections.addInstance("DOWN");
        DynamicDirections.addInstance("LEFT");
        DynamicDirections.addInstance("UP_RIGHT");
        DynamicDirections.addInstance("DOWN_RIGHT");
        DynamicDirections.addInstance("UP_LEFT");
        DynamicDirections.addInstance("DOWN_LEFT");
        DynamicDirections.addInstance("SELF");

        this.width = width;
        this.height = height;
        this.organisms = new ArrayList<>();
        this.tiles = new ArrayList<>();
        this.logs = new ArrayList<>();
    }

    @Override
    protected void createBoard(int width, int height) {
        // Initialize tiles based on width and height
        for (int i = 0; i < width * height; i++) {
            tiles.add(new Tile(i));
        }
        // Set links between tiles
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Tile tile = tiles.get(y * width + x);
                if (y > 0) {
                    tile.setLink(DynamicDirections.get("UP"), tiles.get((y - 1) * width + x));
                }
                if (x < width - 1) {
                    tile.setLink(DynamicDirections.get("RIGHT"), tiles.get(y * width + x + 1));
                }
                if (y < height - 1) {
                    tile.setLink(DynamicDirections.get("DOWN"), tiles.get((y + 1) * width + x));
                }
                if (x > 0) {
                    tile.setLink(DynamicDirections.get("LEFT"), tiles.get(y * width + x - 1));
                }
                if (y > 0 && x < width - 1) {
                    tile.setLink(DynamicDirections.get("UP_RIGHT"), tiles.get((y - 1) * width + x + 1));
                }
                if (y < height - 1 && x < width - 1) {
                    tile.setLink(DynamicDirections.get("DOWN_RIGHT"), tiles.get((y + 1) * width + x + 1));
                }
                if (y > 0 && x > 0) {
                    tile.setLink(DynamicDirections.get("UP_LEFT"), tiles.get((y - 1) * width + x - 1));
                }
                if (y < height - 1 && x > 0) {
                    tile.setLink(DynamicDirections.get("DOWN_LEFT"), tiles.get((y + 1) * width + x - 1));
                }
            }
        }
    }
}