#include "unit.hpp"

Unit::Unit(sf::Vector2i unitPosition)
{
    position = unitPosition;
}

void Unit::SetPosition(sf::Vector2i newPosition)
{
    position = newPosition;
}

sf::Vector2i Unit::GetPosition()
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
