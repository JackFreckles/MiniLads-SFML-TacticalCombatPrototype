#pragma once
#include <SFML/Graphics.hpp>

enum class UnitClass
{
    Knight,           // Sword and Shield (Balanced)
    Barbarian,        // Two-Handed Axe (High Damage), Low health maybe
    Paladin,          // Knight with basic healing magic (Slightly lower health than Knight)
    Rogue,            // Low damage, inflicts status effect with attacks that last multiple turns
    Monk,             // Bare-handed combat (can maybe stun enemies so they lose their next turn)
    Archer,           // Bow and Arrow (Lots of energy, Shooting bow requires more energy per attack than knight for balancing)
    Elemental_Archer, // Archer who shoots magic arrows
    Elemental_Mage,   // Casts magic of element types Water, Wind, Earth, Fire, Light
    White_Mage,       // Magic Healer 
    Summoner          // Very low health, High energy for summoning creatures to fight for them
};

enum class UnitType
{
    Player,
    Enemy
};

class Unit
{
    public:
        Unit(sf::Vector2i unitPosition, int maxEnergy, UnitClass unitClass, UnitType unitType);
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
        int availableEnergy;
        UnitClass unitClass;
        UnitType unitType;

        sf::CircleShape unitShape;
};