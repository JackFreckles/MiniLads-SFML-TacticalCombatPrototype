#include "grid.hpp"
#include <cmath>

Grid::Grid(int inGridWidth, int inGridHeight)
{
    gridWidth = inGridWidth;
    gridHeight = inGridHeight;

    tiles = std::vector(gridWidth, std::vector<Tile>(gridHeight)); // initializes matrix matching grid with each Tile.type set to Grass as default

    // Dirt Tiles
    tiles[1][1].type = TileType::Dirt; tiles[1][2].type = TileType::Dirt; tiles[2][2].type = TileType::Dirt; 
    tiles[2][3].type = TileType::Dirt; tiles[3][3].type = TileType::Dirt; tiles[3][4].type = TileType::Dirt; 
    tiles[4][4].type = TileType::Dirt; tiles[4][5].type = TileType::Dirt; tiles[4][6].type = TileType::Dirt;
    tiles[4][7].type = TileType::Dirt; tiles[4][8].type = TileType::Dirt;

    // Blocked Tiles
    tiles[12][3].type = TileType::Blocked; tiles[12][4].type = TileType::Blocked; tiles[12][5].type = TileType::Blocked;
    tiles[13][5].type = TileType::Blocked; tiles[14][3].type = TileType::Blocked; tiles[14][4].type = TileType::Blocked; 
    tiles[14][5].type = TileType::Blocked;

    // Water Tiles
    tiles[7][3].type = TileType::Water; tiles[8][3].type = TileType::Water; tiles[8][4].type = TileType::Water;
    tiles[9][4].type = TileType::Water; tiles[9][5].type = TileType::Water; tiles[9][6].type = TileType::Water;
    tiles[9][9].type = TileType::Water;

    // Mud Tiles
    tiles[6][3].type = TileType::Mud; tiles[7][4].type = TileType::Mud; tiles[8][5].type = TileType::Mud; 
    tiles[8][6].type = TileType::Mud; tiles[8][7].type = TileType::Mud; tiles[9][7].type = TileType::Mud; 
    tiles[10][7].type = TileType::Mud; tiles[9][3].type = TileType::Mud; tiles[8][8].type = TileType::Mud; 
    tiles[9][8].type = TileType::Mud; tiles[10][8].type = TileType::Mud; tiles[8][9].type = TileType::Mud; 
    tiles[10][9].type = TileType::Mud;
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
            if (tiles[x][y].type == TileType::Grass)
            {
                DrawTile(window, startX + x * tileSize, startY + y * tileSize, sf::Color::Green, sf::Color::Transparent);
            }
            if (tiles[x][y].type == TileType::Dirt)
            {
                DrawTile(window, startX + x * tileSize, startY + y * tileSize, sf::Color(150, 75, 0), sf::Color::Transparent); // sf::Color(150, 75, 0) makes brown
            }
            if (tiles[x][y].type == TileType::Water)
            {
                DrawTile(window, startX + x * tileSize, startY + y * tileSize, sf::Color::Blue, sf::Color::Transparent);
            }
            if (tiles[x][y].type == TileType::Blocked)
            {
                DrawTile(window, startX + x * tileSize, startY + y * tileSize, sf::Color::Black, sf::Color::Transparent);
            }
            if (tiles[x][y].type == TileType::Mud)
            {
                DrawTile(window, startX + x * tileSize, startY + y * tileSize, sf::Color(101, 67, 33), sf::Color::Transparent); // sf::Color(101, 67, 33) makes dark brown
            }
        }
    }

    if (selectedTile != sf::Vector2i(-1,-1))
    {
        DrawTile(window, startX + selectedTile.x * tileSize, startY + selectedTile.y * tileSize, sf::Color::Transparent, sf::Color::Yellow);
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
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

    return {static_cast<int>(std::floor((worldPosition.x - startX) / tileSize)), static_cast<int>(std::floor((worldPosition.y - startY) / tileSize))};
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
    if (IsValidTile(tile))
    {
        return tiles[tile.x][tile.y].type;
    }
    else
    {
        return TileType::Blocked;
    }
}

sf::Vector2f Grid::ConvertTileToScreenPosition(sf::Vector2i unitPosition)
{
    return {unitPosition.x * tileSize + startX, unitPosition.y * tileSize + startY};
}

bool Grid::IsTileWalkable(sf::Vector2i tile)
{
    if (!IsValidTile(tile)) // if tile outside grid is somehow selected then return false (Tile is blocked)
    {
        return false;
    }

    if (tiles[tile.x][tile.y].type == TileType::Blocked || tiles[tile.x][tile.y].type == TileType::Water)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Grid::IsTileOccupied(sf::Vector2i tile)
{
    if (IsValidTile(tile))
    {
        if (tiles[tile.x][tile.y].occupation == Occupation::Occupied)
        {
            return true;
        }
    }
    return false;
}

void Grid::SetTileOccupation(sf::Vector2i tile, Occupation occupancy)
{
    if (!IsValidTile(tile))
    {
    }
    else
    {
        tiles[tile.x][tile.y].occupation = occupancy;
    }
}