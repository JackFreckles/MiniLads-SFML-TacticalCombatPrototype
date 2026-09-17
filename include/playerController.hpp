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
        void SetTileToMoveTo(sf::Vector2i newTile);
        void SlideToNewTile(float dt);//, sf::Vector2i newTile);
        void GetPath();
        std::vector<sf::Vector2i> GetFoundPath();
        int GetPathIndex();
        int GetMaxPathIndex();
        void SetPathStep();

    private:
        Unit &playerUnitRef;
        Grid &grid;
        sf::Vector2i tileToMoveTo;
        int movementRange = 10;
        float movementSpeed = 200;
        int pathIndex = 0;
        int maxPathIndex = 0;
        std::vector<sf::Vector2i> foundPath;
        sf::Vector2i nextPathStep;
};