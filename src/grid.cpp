#include "grid.hpp"
#include <cmath>

Grid::Grid(int inGridWidth, int inGridHeight)
{
    gridWidth = inGridWidth;
    gridHeight = inGridHeight;

    tiles = std::vector(gridWidth, std::vector<TileType>(gridHeight, TileType::Grass)); // initializes matrix matching grid with each TileState set to Normal as default
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
    sf::Vector2i blockedTile{10,3};
    sf::Vector2i dirtTile{10, 4};
    sf::Vector2i waterTile{10, 5};

    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            if (x == blockedTile.x && y == blockedTile.y)
            {
                tiles[x][y] = TileType::Blocked;
            }
            if (x == dirtTile.x && y == dirtTile.y)
            {
                tiles[x][y] = TileType::Mud;
            }
            if (x == waterTile.x && y == waterTile.y)
            {
                tiles[x][y] = TileType::Water;
            }

            if (tiles[x][y] == TileType::Grass)
            {
                DrawTile(window, startX + x * tileSize, startY + y * tileSize, sf::Color::Green, sf::Color::Transparent);
            }
            if (tiles[x][y] == TileType::Mud)
            {
                DrawTile(window, startX + x * tileSize, startY + y * tileSize, sf::Color(165, 42, 42), sf::Color::Transparent); // sf::Color(165, 42, 42) makes brown
            }
            if (tiles[x][y] == TileType::Water)
            {
                DrawTile(window, startX + x * tileSize, startY + y * tileSize, sf::Color::Blue, sf::Color::Transparent);
            }
        }
    }

    if (selectedTile != sf::Vector2i(-1,-1))
    {
        DrawTile(window, startX + selectedTile.x * tileSize, startY + selectedTile.y * tileSize, sf::Color::Transparent, sf::Color::Yellow);
    }

    if (tiles[blockedTile.x][blockedTile.y] == TileType::Blocked)
    {
        DrawTile(window, startX + blockedTile.x * tileSize, startY + blockedTile.y * tileSize, sf::Color::Black, sf::Color::Transparent);
    }
}

sf::Vector2f Grid::GetScreenPositionOfTileAtMouse(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    return {((mousePosition.x - startX) / tileSize * tileSize) + startX, ((mousePosition.y - startY) / tileSize * tileSize) + startY};
}

sf::Vector2i Grid::GetTileAtMouse(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    return {static_cast<int>(std::floor((mousePosition.x - startX) / tileSize)), static_cast<int>(std::floor((mousePosition.y - startY) / tileSize))};
}

void Grid::HighlightHoveredTile(sf::RenderWindow& window, sf::Vector2i tileMouseIsOn)
{
    if (IsValidTile(tileMouseIsOn))
    {
        sf::Vector2f screenPosition = ConvertTileToScreenPosition(tileMouseIsOn);

        DrawTile(window, screenPosition.x, screenPosition.y, sf::Color::Transparent, sf::Color::Red);
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

sf::Vector2i Grid::GetSelectedTile()
{
    return selectedTile;
}

TileType Grid::GetTileType(sf::Vector2i tile)
{
    return tiles[tile.x][tile.y];
}

sf::Vector2f Grid::ConvertTileToScreenPosition(sf::Vector2i unitPosition)
{
    return {unitPosition.x * tileSize + startX, unitPosition.y * tileSize + startY};
}

bool Grid::IsTileWalkable(sf::Vector2i tile)
{
    if (!IsValidTile(tile)) // if tile outside grid is somehow selected then return true (Tile is blocked)
    {
        return true;
    }

    if (tiles[tile.x][tile.y] == TileType::Blocked || tiles[tile.x][tile.y] == TileType::Water)
    {
        return false;
    }
    else
    {
        return true;
    }
}