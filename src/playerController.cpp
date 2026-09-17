#include "playerController.hpp"
#include <iostream>

PlayerController::PlayerController(Unit &playerUnit, Grid &grid) : playerUnitRef(playerUnit), grid(grid)
{
    tileToMoveTo = playerUnit.GetPosition();
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

void PlayerController::SetTileToMoveTo(sf::Vector2i newTile)
{
    tileToMoveTo = newTile;
}

void PlayerController::SlideToNewTile(float dt)//, sf::Vector2i newTile)
{
    sf::Vector2f playerPixel = playerUnitRef.GetVisiblePosition();
    sf::Vector2f targetPixel = grid.ConvertTileToScreenPosition(nextPathStep);
    sf::Vector2f direction = {targetPixel.x - playerPixel.x, targetPixel.y - playerPixel.y};
    float vectorLength = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
    if (vectorLength != 0)
    {
        if (vectorLength <= movementSpeed * dt)
        {
            playerUnitRef.SetVisiblePosition(grid.ConvertTileToScreenPosition(nextPathStep));
            playerUnitRef.SetPosition(foundPath[pathIndex]);
            if (pathIndex < maxPathIndex)
            {
                pathIndex++;
                SetPathStep();
            }
        }
        else
        {
            sf::Vector2f unitVector = {direction.x / vectorLength, direction.y / vectorLength};
            sf::Vector2f newVisiblePosition = {playerPixel.x + (movementSpeed * dt * unitVector.x), playerPixel.y + (movementSpeed * dt * unitVector.y)};
            playerUnitRef.SetVisiblePosition(newVisiblePosition);
        }
    }
}

void PlayerController::GetPath()
{
    Pathfinder path(grid, playerUnitRef.GetPosition(), tileToMoveTo);
    foundPath = path.ReconstructPath(path.FindPath());
    if (foundPath.size() > 1)
    {
        pathIndex = 1;
        maxPathIndex = foundPath.size() - 1;
    }
    else
    {
        pathIndex = 0;
        maxPathIndex = 0;
    }
}

std::vector<sf::Vector2i> PlayerController::GetFoundPath()
{
    return foundPath;
}

int PlayerController::GetPathIndex()
{
    return pathIndex;
}

int PlayerController::GetMaxPathIndex()
{
    return maxPathIndex;
}

void PlayerController::SetPathStep()
{
    nextPathStep = foundPath[pathIndex];
}