#include "grid.hpp"
#include <cmath>

Grid::Grid(int inGridWidth, int inGridHeight)
{
    gridWidth = inGridWidth;
    gridHeight = inGridHeight;

    tiles = std::vector(gridWidth, std::vector<TileState>(gridHeight, TileState::Normal)); // initializes matrix matching grid with each TileState set to Normal as default
}

void Grid::DrawTile(sf::RenderWindow& window, float x, float y, sf::Color fillColor, sf::Color borderColor)
{
    sf::RectangleShape tile({tileSize, tileSize});
    tile.setPosition({x, y});
    tile.setFillColor(fillColor);
    tile.setOutlineColor(borderColor);
    tile.setOutlineThickness(2.f);

    window.draw(tile);
}

void Grid::DrawGrid(sf::RenderWindow& window)
{
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            DrawTile(window, startX + x * tileSize, startY + y * tileSize, sf::Color::Green, sf::Color::Black);
        }
    }

    if (selectedTile != sf::Vector2i(-1,-1))
    {
        DrawTile(window, startX + selectedTile.x * tileSize, startY + selectedTile.y * tileSize, sf::Color::Transparent, sf::Color::Yellow);
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
        DrawTile(window, mousePositionOnScreen.x, mousePositionOnScreen.y, sf::Color::Transparent, sf::Color::Red);
    }
}

bool Grid::IsValidTile(sf::Vector2i tile)
{
    return tile.x >= 0 && tile.x < gridWidth && tile.y >= 0 && tile.y < gridHeight;
}

void Grid::SetSelectedTile(sf::Vector2i tileMouseIsOn)
{
    if (IsValidTile(tileMouseIsOn))
    {
        selectedTile = tileMouseIsOn;
    }
}

sf::Vector2f Grid::ConvertUnitPositionToPixel(sf::Vector2f unitPosition)
{
    return {unitPosition.x * tileSize + startX, unitPosition.y * tileSize + startY};
}