#pragma once
#include <SFML/Graphics.hpp>

class Unit
{
    public:
    Unit(sf::Vector2i unitPosition, int maxEnergy);
    sf::Vector2i GetPosition();
    void SetPosition(sf::Vector2i newPosition);
    sf::Vector2f GetVisiblePosition();
    void SetVisiblePosition(sf::Vector2f newVisiblePosition);
    void Draw(sf::RenderWindow &window, sf::Vector2f pixelPosition);
    void SpendEnergy(int amountSpent);
    int GetAvailableEnergy();
    int GetMaxEnergy();
    void ResetAvailableEnergy();


    private:
    sf::Vector2i position;
    sf::Vector2f visiblePosition;
    int maxEnergy;
    int availableEnergy = maxEnergy;
};