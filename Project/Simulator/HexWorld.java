package Simulator;

import java.util.ArrayList;

import Utils.DynamicDirections;

public class HexWorld extends World {

    public HexWorld(int width, int height, boolean hex) {
        super(width, height, hex);

        DynamicDirections.clear();

        DynamicDirections.addInstance("NORTH");
        DynamicDirections.addInstance("NORTH_EAST");
        DynamicDirections.addInstance("SOUTH_EAST");
        DynamicDirections.addInstance("SOUTH");
        DynamicDirections.addInstance("SOUTH_WEST");
        DynamicDirections.addInstance("NORTH_WEST");
        DynamicDirections.addInstance("SELF");

        this.width = width;
        this.height = height;
        this.organisms = new ArrayList<>();
        this.tiles = new ArrayList<>();
        this.logs = new ArrayList<>();

        createBoard(width, height);
    }

    public HexWorld() {
        this(20, 20, true);
    }

    @Override
    public void createBoard(int width, int height) {
        // Initialize tiles based on width and height
        for (int i = 0; i < width * height; i++) {
            tiles.add(new Tile(i, 6));
        }
        // Set links between tiles
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Tile tile = tiles.get(y * width + x);
                if (y > 0) {
                    tile.setLink(DynamicDirections.get("NORTH"), tiles.get((y - 1) * width + x));
                }
                if (x < width - 1) {
                    tile.setLink(DynamicDirections.get("NORTH_EAST"), tiles.get(y * width + x + 1));
                }
                if (y < height - 1) {
                    tile.setLink(DynamicDirections.get("SOUTH_EAST"), tiles.get((y + 1) * width + x));
                }
                if (x > 0) {
                    tile.setLink(DynamicDirections.get("SOUTH"), tiles.get(y * width + x - 1));
                }
            }
        }
    }
}