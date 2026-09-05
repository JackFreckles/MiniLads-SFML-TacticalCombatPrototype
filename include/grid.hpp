#pragma once
#include <SFML/Graphics.hpp>

class Grid
{
    public:
        Grid(int inGridWidth, int inGridHeight);
        void DrawTile(sf::RenderWindow& window, float x, float y, sf::Color color);
        void DrawGrid(sf::RenderWindow& window);
        sf::Vector2i GetScreenPositionOfTileAtMouse(sf::RenderWindow& window);
        sf::Vector2i GetTileAtMouse(sf::RenderWindow& window);
        void HighlightHoveredTile(sf::RenderWindow& window, sf::Vector2i mousePositionOnScreen, sf::Vector2i tileMouseIsOn);
        bool IsValidTile(sf::Vector2i tile);

    private:
        float tileSize = 64.f;
        float startX = 70.f;
        float startY = 50.f;
        int gridWidth = 18;
        int gridHeight = 10;
};