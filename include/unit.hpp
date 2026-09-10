#pragma once
#include <SFML/Graphics.hpp>

class Unit
{
    public:
    Unit(sf::Vector2f unitPosition);
    sf::Vector2f GetPosition();
    void SetPosition(sf::Vector2f newPosition);

    void Draw(sf::RenderWindow &window, sf::Vector2f pixelPosition);

    private:
    sf::Vector2f position;
};