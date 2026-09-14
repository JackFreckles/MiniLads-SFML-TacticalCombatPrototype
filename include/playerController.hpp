#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "unit.hpp"
#include "grid.hpp"
#include "pathfinder.hpp"

class PlayerController
{
    public:
        PlayerController(Unit &playerUnit, Grid &grid);
        void MoveToNewTile(sf::Vector2i newTile);
        sf::Vector2i GetTileToMoveTo();
        void SlideToNewTile(float dt, sf::Vector2i newTile);

    private:
        Unit &playerUnitRef;
        Grid &grid;
        sf::Vector2i tileToMoveTo;
        int movementRange = 10;
        float movementSpeed = 200;
};