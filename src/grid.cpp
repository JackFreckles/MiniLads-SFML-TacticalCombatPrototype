#include "grid.hpp"
#include <cmath>

Grid::Grid(int inGridWidth, int inGridHeight)
{
    gridWidth = inGridWidth;
    gridHeight = inGridHeight;
}

void Grid::DrawTile(sf::RenderWindow& window, float x, float y, sf::Color color)
{
    sf::RectangleShape tile({tileSize, tileSize});
    tile.setPosition({x, y});
    tile.setFillColor(color);
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
            DrawTile(window, startX + x * tileSize, startY + y * tileSize, sf::Color::Green);
        }
    }
}

sf::Vector2i Grid::GetScreenPositionOfTileAtMouse(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    return {(static_cast<int>((mousePosition.x - startX) / tileSize) * static_cast<int>(tileSize)) + static_cast<int>(startX), (static_cast<int>((mousePosition.y - startY) / tileSize) * static_cast<int>(tileSize)) + static_cast<int>(startY)};
}

sf::Vector2i Grid::GetTileAtMouse(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    return {static_cast<int>(std::floor((mousePosition.x - startX) / tileSize)), static_cast<int>(std::floor((mousePosition.y - startY) / tileSize))};
}

void Grid::HighlightHoveredTile(sf::RenderWindow& window, sf::Vector2i mousePositionOnScreen, sf::Vector2i tileMouseIsOn)
{
    if (IsValidTile(tileMouseIsOn))
    {
        DrawTile(window, mousePositionOnScreen.x, mousePositionOnScreen.y, sf::Color::Blue);
    }
}

bool Grid::IsValidTile(sf::Vector2i tile)
{
    return tile.x >= 0 && tile.x < gridWidth && tile.y >= 0 && tile.y < gridHeight;
}