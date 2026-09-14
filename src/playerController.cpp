#include "playerController.hpp"

PlayerController::PlayerController(Unit &playerUnit, Grid &grid) : playerUnitRef(playerUnit), grid(grid)
{
    playerUnitRef.SetVisiblePosition(grid.ConvertTileToScreenPosition(playerUnitRef.GetPosition()));
}

void PlayerController::MoveToNewTile(sf::Vector2i newTile)
{
    sf::Vector2i playerTile = playerUnitRef.GetPosition();
    int distance = std::abs(newTile.x - playerTile.x) + std::abs(newTile.y - playerTile.y); // Manhattan distance equation
    if (distance <= movementRange && grid.IsTileWalkable(newTile))
    {
        playerUnitRef.SetPosition(newTile);
        tileToMoveTo = newTile;
    }
}

sf::Vector2i PlayerController::GetTileToMoveTo()
{
    return tileToMoveTo;
}

void PlayerController::SlideToNewTile(float dt, sf::Vector2i newTile)
{
    sf::Vector2f playerPixel = playerUnitRef.GetVisiblePosition();
    sf::Vector2f targetPixel = grid.ConvertTileToScreenPosition(newTile);
    sf::Vector2f direction = {targetPixel.x - playerPixel.x, targetPixel.y - playerPixel.y};
    float vectorLength = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
    if (vectorLength != 0)
    {
        sf::Vector2f unitVector = {direction.x / vectorLength, direction.y / vectorLength};
        sf::Vector2f newVisiblePosition = {playerPixel.x + (movementSpeed * dt * unitVector.x), playerPixel.y + (movementSpeed * dt * unitVector.y)};
        if (vectorLength <= movementSpeed * dt)
        {
            playerUnitRef.SetVisiblePosition(grid.ConvertTileToScreenPosition(newTile));
        }
        else
        {
            playerUnitRef.SetVisiblePosition(newVisiblePosition);
        }
    }
}