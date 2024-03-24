#include "@Organism.hpp"

#include <nlohmann/json.hpp>

#include "../Tile.hpp"
#include "../World.hpp"

Organism::Organism(nlohmann::json j, World &world)
    : type(static_cast<Type>(j["type"].get<u_int8_t>())),
      power(j["power"].get<int>()),
      initiative(j["initiative"].get<int>()),
      age(j["age"].get<u_int32_t>()),
      alive(j["alive"].get<bool>()),
      reproduction_cooldown(j["reproduction_cooldown"].get<int>()),
      skip(j["skip"].get<bool>()),
      world(world),
      tile(world.getTile(j["tile_index"].get<size_t>())) {}

Organism::Organism(Type type, int power, int initiative, World &world)
    : type(type), power(power), initiative(initiative), world(world) {}

Tile *Organism::getTile() const { return tile; }
void Organism::setTile(Tile *tile) { this->tile = tile; }

void Organism::Age() {
    if (reproduction_cooldown > 0) reproduction_cooldown--;
    age++;
}

void Organism::Die() { alive = false; }
bool Organism::isDead() const { return !alive; }
bool Organism::isAlive() const { return alive; }
void Organism::skipTurn() { skip = true; }
void Organism::unskipTurn() { skip = false; }
bool Organism::isSkipped() const { return skip; }

int Organism::getPower() const { return power; }
int Organism::getInitiative() const { return initiative; }
int Organism::getAge() const { return age; }
void Organism::setPower(int power) { this->power = power; }
void Organism::setInitiative(int initiative) { this->initiative = initiative; }
Organism::~Organism() {}

nlohmann::json Organism::toJson() const {
    return {{"type", static_cast<u_int8_t>(type)},
            {"power", power},
            {"initiative", initiative},
            {"age", age},
            {"alive", alive},
            {"reproduction_cooldown", reproduction_cooldown},
            {"skip", skip},
            {"tile_index", tile->index}};
}