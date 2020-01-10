#pragma once

#include "models/Player.hpp"
#include "World.hpp"

// A singleton, central model in the system
class Game {
public:
    static Game &getInstance() {
        static Game instance;
        return instance;
    }

private:
    Game() : player(glm::vec3(0, 90, 0)) {}

public:
    World world;
    Player player;

    Game(Game const &) = delete;

    void operator=(const Game &) = delete;
};