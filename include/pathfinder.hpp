#pragma once
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "unit.hpp"

struct Tile
{
    sf::Vector2i position; // Where am I?
    int g; // Distance currently traveled from start
    int h; // Estimated distance from to destination
    int f; // Final/Total cost of path (g + h)
    sf::Vector2i parent; // Where did I come from?
};

class Pathfinder
{
    public:
        Pathfinder(Grid &grid, Unit &unit);

    private:
        Grid &grid;
        Unit &unit;

        std::vector<sf::Vector2i> finalPath;

};