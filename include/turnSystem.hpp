#pragma once
#include "unit.hpp"

enum class TurnState
{
    PlayerTurn,
    EnemyTurn
};

class TurnSystem
{
    public:
    TurnSystem(Unit& playerUnit, Unit& enemyUnit);
    void EndTurn();
    TurnState GetWhoseTurn();

    private:
    TurnState whoseTurn;
    Unit& playerUnitRef;
    Unit& enemyUnitRef;
};