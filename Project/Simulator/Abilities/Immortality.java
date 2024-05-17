package Simulator.Abilities;

import Simulator.Tile;
import Simulator.Organisms.Organism;
import Simulator.Organisms.Animals.Animal;
import Simulator.Organisms.Animals.Human;

public class Immortality extends Ability {
    public Immortality(int cooldown, int duration) {
        super(cooldown, duration);
    }

    public Immortality(int cooldown, int duration, int defaultCooldown, int defaultDuration) {
        super(cooldown, duration, 5, 5);
    }

    @Override
    public void effect(Organism user, Organism other) {
        Tile newTile = user.getTile().getRandomFreeNeighbour();
        if (newTile == null) {
            newTile = user.getTile().getRandomNeighbour();
        }
        if (newTile == null) {
            if (other instanceof Animal) {
                ((Animal) other).undoMove();
            }
            return;
        }
        if (user instanceof Human) {
            ((Human) user).move(newTile);
        }
        if (user.getTile().getOrganismCount() > 1) {
            user.collision(user.getTile().getOrganism());
        }
    }

    @Override
    public void effect(Organism user) {
        Tile newTile = user.getTile().getRandomFreeNeighbour();
        if (newTile == null)
            return;
        if (user instanceof Human) {
            ((Human) user).move(newTile);
        }
    }
}