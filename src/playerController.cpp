#include "playerController.hpp"

PlayerController::PlayerController(Unit &playerUnit, Grid &grid) : playerUnitRef(playerUnit), grid(grid)
{

}

void PlayerController::MoveToNewTile(sf::Vector2i newTile)
{
    sf::Vector2i playerTile = playerUnitRef.GetPosition();
    int distance = std::abs(newTile.x - playerTile.x) + std::abs(newTile.y - playerTile.y); // Manhattan distance equation
    if (distance <= movementRange && !grid.IsTileBlocked(newTile))
    {
        playerUnitRef.SetPosition(newTile);
    }
}

sf::Vector2i PlayerController::GetTileToMoveTo()
{
    return tileToMoveTo;
}

