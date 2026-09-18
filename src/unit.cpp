#include "unit.hpp"

Unit::Unit(sf::Vector2i unitPosition, int maxEnergy) : position(unitPosition), maxEnergy(maxEnergy)
{
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

sf::Vector2f Unit::GetVisiblePosition()
{
    return visiblePosition;
}

void Unit::SetVisiblePosition(sf::Vector2f newVisiblePosition)
{
    visiblePosition = newVisiblePosition;
}

void Unit::SpendEnergy(int amountSpent)
{
    if (amountSpent <= availableEnergy)
    {
        availableEnergy -= amountSpent;
    }
}

int Unit::GetAvailableEnergy()
{
    return availableEnergy;
}

int Unit::GetMaxEnergy()
{
    return maxEnergy;
}

void Unit::ResetAvailableEnergy()
{
    availableEnergy = maxEnergy;
}