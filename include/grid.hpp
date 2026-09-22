#pragma once
#include <SFML/Graphics.hpp>
#include "unit.hpp"

enum class TileType
{
    Grass,
    Blocked,
    Mud,
    Dirt,
    Water
};

enum class Occupation
{
    Unoccupied,
    Occupied
};

struct Tile
{
    TileType type = TileType::Grass;
    Occupation occupation = Occupation::Unoccupied;
};

class Grid
{
    public:
        Grid(int inGridWidth, int inGridHeight);
        void DrawTile(sf::RenderWindow& window, float x, float y, sf::Color fillColor, sf::Color borderColor);
        void DrawGrid(sf::RenderWindow& window);
        sf::Vector2f GetScreenPositionOfTileAtMouse(sf::RenderWindow& window);
        sf::Vector2i GetTileAtMouse(sf::RenderWindow& window);
        void HighlightHoveredTile(sf::RenderWindow& window, sf::Vector2i tileMouseIsOn);
        bool IsValidTile(sf::Vector2i tile);
        sf::Vector2i SelectTile(sf::RenderWindow& window, sf::Vector2i mousePositionOnScreen, sf::Vector2i tileMouseIsOn);
        void SetSelectedTile(sf::Vector2i tileMouseIsOn);
        sf::Vector2i GetSelectedTile();
        TileType GetTileType(sf::Vector2i tile);
        bool IsTileWalkable(sf::Vector2i tile);
        bool IsTileOccupied(sf::Vector2i tile);
        void SetTileOccupation(sf::Vector2i tile, Occupation occupancy);

        sf::Vector2f ConvertTileToScreenPosition(sf::Vector2i unitPosition);

    private:
        float tileSize = 64.f;
        float startX = 70.f;
        float startY = 50.f;
        int gridWidth = 0;
        int gridHeight = 0;
        std::vector<std::vector<Tile>> tiles;
        sf::Vector2i selectedTile{-1,-1};
};