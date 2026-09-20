#include "turnSystem.hpp"

TurnSystem::TurnSystem(Unit& playerUnit, Unit& enemyUnit) : whoseTurn(TurnState::PlayerTurn), playerUnitRef(playerUnit), enemyUnitRef(enemyUnit)
{

}

void TurnSystem::EndTurn()
{
    switch (whoseTurn)
    {
        case (TurnState::PlayerTurn):
        {
            enemyUnitRef.ResetAvailableEnergy();
            whoseTurn = TurnState::EnemyTurn;
            break;
        }
        case (TurnState::EnemyTurn):
        {
            playerUnitRef.ResetAvailableEnergy();
            whoseTurn = TurnState::PlayerTurn;
            break;
        }
    }
}

TurnState TurnSystem::GetWhoseTurn()
{
    return whoseTurn;
}