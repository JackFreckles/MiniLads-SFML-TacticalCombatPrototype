#include "Grid.hpp"
// #include <SFML/Graphics.hpp>

Grid::Grid()
{
    // sf::RectangleShape tile;
    // tile.setSize({x, y});
}

void Grid::DrawTile(sf::RenderWindow& window, float x, float y)
{
    sf::RectangleShape tile({x, y});
    tile.setPosition({100.f, 100.f});
    tile.setFillColor(sf::Color::Red);

    window.draw(tile);
}

void Grid::DrawGrid(sf::RenderWindow& window, int gridWidth, int gridHeight)
{
    sf::RectangleShape tile({tileSize, tileSize});
    tile.setFillColor(sf::Color::Green);
    tile.setOutlineColor(sf::Color::Black);
    tile.setOutlineThickness(2.f);

    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            tile.setPosition({startX + x * tileSize, startY + y * tileSize});
            window.draw(tile);
        }
    }
}