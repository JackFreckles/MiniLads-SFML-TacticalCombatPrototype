#pragma once
#include <SFML/Graphics.hpp>

class Unit
{
    public:
    Unit(sf::Vector2i unitPosition);
    sf::Vector2i GetPosition();
    void SetPosition(sf::Vector2i newPosition);
    sf::Vector2f GetVisiblePosition();
    void SetVisiblePosition(sf::Vector2f newVisiblePosition);
    int GetMovementCount();
    void SetMovementCount(int newMovementCount);

    void Draw(sf::RenderWindow &window, sf::Vector2f pixelPosition);

    private:
    sf::Vector2i position;
    sf::Vector2f visiblePosition;
    int movementCount = 0;
};