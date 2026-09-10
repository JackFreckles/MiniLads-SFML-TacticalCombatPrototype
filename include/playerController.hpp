#pragma once
#include <SFML/Graphics.hpp>
#include "unit.hpp"
#include "grid.hpp"

class PlayerController
{
    public:
        PlayerController(Unit &playerUnit, Grid &grid);
        void MoveToNewTile(sf::Vector2i newTile);
        sf::Vector2i GetTileToMoveTo();

    private:
        Unit &playerUnitRef;
        Grid &grid;
        sf::Vector2i tileToMoveTo;
        int movementRange = 2;
};