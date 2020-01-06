#pragma once

#include "world/world.hpp"
#include "models/Player.hpp"

// A singleton, central model in the system
class Game
{
public:
    static Game& getInstance()
    {
        static Game instance;
        return instance;
    };

private:
    Game(): player(0, 90, 0) 
    {
        std::cout << "Game created" << std::endl;
    };

public:
    World world;
    PlayerT player;

    Game(Game const&) = delete;
    void operator=(const Game &) = delete;
};