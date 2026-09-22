#include "unit.hpp"

Unit::Unit(sf::Vector2i unitPosition, int maxEnergy, UnitClass unitClass, UnitType unitType) 
: position(unitPosition), maxEnergy(maxEnergy), availableEnergy(maxEnergy), unitClass(unitClass), unitType(unitType)
{
    switch (unitClass)
    {
        case (UnitClass::Archer):
            unitShape.setRadius(32.0f);
            unitShape.setPointCount(3);
            break;
        case (UnitClass::Barbarian):
            unitShape.setRadius(32.0f);
            unitShape.setPointCount(4);
            break;
        case (UnitClass::Elemental_Archer):
            unitShape.setRadius(32.0f);
            unitShape.setPointCount(5);
            break;
        case (UnitClass::Elemental_Mage):
            unitShape.setRadius(32.0f);
            unitShape.setPointCount(6);
            break;
        case (UnitClass::Knight):
            unitShape.setRadius(32.0f);
            unitShape.setPointCount(7);
            break;
        case (UnitClass::Monk):
            unitShape.setRadius(32.0f);
            unitShape.setPointCount(8);
            break;
        case (UnitClass::Paladin):
            unitShape.setRadius(32.0f);
            unitShape.setPointCount(9);
            break;
        case (UnitClass::Rogue):
            unitShape.setRadius(32.0f);
            unitShape.setPointCount(10);
            break;
        case (UnitClass::Summoner):
            unitShape.setRadius(32.0f);
            unitShape.setPointCount(11);
            break;
        case (UnitClass::White_Mage):
            unitShape.setRadius(32.0f);
            unitShape.setPointCount(12);
            break;
    }

    switch (unitType)
    {
        case (UnitType::Player):
            unitShape.setFillColor(sf::Color::White);
            break;
        case (UnitType::Enemy):
            unitShape.setFillColor(sf::Color::Red);
            break;
    }
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
    unitShape.setPosition(pixelPosition);
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