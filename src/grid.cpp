#include "grid.hpp"

Grid::Grid(int inGridWidth, int inGridHeight)
{
    gridWidth = inGridWidth;
    gridHeight = inGridHeight;
}

void Grid::DrawTile(sf::RenderWindow& window, float x, float y)
{
    sf::RectangleShape tile({tileSize, tileSize});
    tile.setPosition({x, y});
    tile.setFillColor(sf::Color::Green);
    tile.setOutlineColor(sf::Color::Black);
    tile.setOutlineThickness(2.f);

    window.draw(tile);
}

void Grid::DrawGrid(sf::RenderWindow& window)
{
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            DrawTile(window, startX + x * tileSize, startY + y * tileSize);
        }
    }
}

sf::Vector2i Grid::GetTileAtMouse(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    return {static_cast<int>((mousePosition.x - startX) / tileSize), static_cast<int>((mousePosition.y - startY) / tileSize)};
}