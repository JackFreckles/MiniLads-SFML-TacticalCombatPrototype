#include "unit.hpp"

Unit::Unit(sf::Vector2f unitPosition)
{
    position = unitPosition;
}

void Unit::SetPosition(sf::Vector2f newPosition)
{
    position = newPosition;
}

sf::Vector2f Unit::GetPosition()
{
    return position;
}

void Unit::Draw(sf::RenderWindow &window, sf::Vector2f pixelPosition)
{
    sf::CircleShape unitShape(32.0f);
    unitShape.setPosition(pixelPosition);
    unitShape.setFillColor(sf::Color::Blue);

    window.draw(unitShape);
}
