#pragma once
#include <SFML/Graphics.hpp>

class Unit
{
    public:
    Unit(sf::Vector2i unitPosition);
    sf::Vector2i GetPosition();
    void SetPosition(sf::Vector2i newPosition);

    void Draw(sf::RenderWindow &window, sf::Vector2f pixelPosition);

    private:
    sf::Vector2i position;
};