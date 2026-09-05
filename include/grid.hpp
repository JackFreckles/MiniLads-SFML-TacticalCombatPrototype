#pragma once
#include <SFML/Graphics.hpp>

class Grid
{
    public:
        Grid();
        void DrawTile(sf::RenderWindow& window, float x, float y);
        void DrawGrid(sf::RenderWindow& window, int gridWidth, int gridHeight);

    private:
        float tileSize = 64.f;
        float startX = 70.f;
        float startY = 50.f;
};