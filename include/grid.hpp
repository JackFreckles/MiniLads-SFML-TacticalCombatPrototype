#pragma once
#include <SFML/Graphics.hpp>

class Grid
{
    public:
        Grid(int inGridWidth, int inGridHeight);
        void DrawTile(sf::RenderWindow& window, float x, float y);
        void DrawGrid(sf::RenderWindow& window);
        sf::Vector2i GetTileAtMouse(sf::RenderWindow& window);

    private:
        float tileSize = 64.f;
        float startX = 70.f;
        float startY = 50.f;
        int gridWidth = 0;
        int gridHeight = 0;
};