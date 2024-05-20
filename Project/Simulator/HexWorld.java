package Simulator;

import java.util.ArrayList;

import Utils.DynamicDirections;

public class HexWorld extends World {

    public HexWorld(int width, int height) {
        super(true);

        DynamicDirections.clear();

        DynamicDirections.addInstance("UP");
        DynamicDirections.addInstance("DOWN");
        DynamicDirections.addInstance("TOP_LEFT");
        DynamicDirections.addInstance("TOP_RIGHT");
        DynamicDirections.addInstance("BOTTOM_LEFT");
        DynamicDirections.addInstance("BOTTOM_RIGHT");
        DynamicDirections.addInstance("SELF");

        this.width = width;
        this.height = height;
        this.organisms = new ArrayList<>();
        this.tiles = new ArrayList<>();
        this.logs = new ArrayList<>();

        createBoard(width, height);
    }

    public HexWorld() {
        this(20, 20);
    }

    @Override
    public void createBoard(int width, int height) {
        int size = width * height;

        for (int i = 0; i < size; i++) {
            tiles.add(new Tile(i, 6));
        }

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                Tile tile = tiles.get(y * width + x);

                int indexUp = (y - 1) * width + (x - 1);
                Tile up = (indexUp >= 0 && indexUp < tiles.size()) ? tiles.get(indexUp) : null;
                int indexDown = (y + 1) * width + (x + 1);
                Tile down = (indexDown >= 0 && indexDown < tiles.size()) ? tiles.get(indexDown) : null;
                int indexBottomRight = (y) * width + (x + 1);
                Tile bottom_right = (indexBottomRight >= 0 && indexBottomRight < tiles.size())
                        ? tiles.get(indexBottomRight)
                        : null;
                int indexBottomLeft = (y + 1) * width + (x);
                Tile bottom_left = (indexBottomLeft >= 0 && indexBottomLeft < tiles.size()) ? tiles.get(indexBottomLeft)
                        : null;
                int indexTopRight = (y - 1) * width + (x);
                Tile top_right = (indexTopRight >= 0 && indexTopRight < tiles.size()) ? tiles.get(indexTopRight) : null;
                int indexTopLeft = (y) * width + (x - 1);
                Tile top_left = (indexTopLeft >= 0 && indexTopLeft < tiles.size()) ? tiles.get(indexTopLeft) : null;

                tile.setLink(DynamicDirections.get("UP"), up);
                tile.setLink(DynamicDirections.get("DOWN"), down);
                tile.setLink(DynamicDirections.get("TOP_LEFT"), top_left);
                tile.setLink(DynamicDirections.get("TOP_RIGHT"), top_right);
                tile.setLink(DynamicDirections.get("BOTTOM_LEFT"), bottom_left);
                tile.setLink(DynamicDirections.get("BOTTOM_RIGHT"), bottom_right);

            }
        }

    }

    @Override
    public int getDistance(Tile start, Tile target) {
        int x1 = start.index % width;
        int y1 = start.index / width;
        int x2 = target.index % width;
        int y2 = target.index / width;

        int dx = Math.abs(x1 - x2);
        int dy = Math.abs(y1 - y2);

        if (dx > dy) {
            return dx;
        } else {
            return dy + (dx - dy) / 2;
        }
    }
}