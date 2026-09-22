#include "playerController.hpp"
#include <iostream>

PlayerController::PlayerController(Unit &playerUnit, Grid &grid) : playerUnitRef(playerUnit), grid(grid)
{
    tileToMoveTo = playerUnit.GetPosition();
    playerUnitRef.SetVisiblePosition(grid.ConvertTileToScreenPosition(playerUnitRef.GetPosition()));
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
    if (!followingPath)
    {
        followingPath = true;
    }
    sf::Vector2f playerPixel = playerUnitRef.GetVisiblePosition();
    sf::Vector2f targetPixel = grid.ConvertTileToScreenPosition(nextPathStep);
    sf::Vector2f direction = {targetPixel.x - playerPixel.x, targetPixel.y - playerPixel.y};
    float vectorLength = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
    if (vectorLength != 0)
    {
        if (vectorLength <= movementSpeed * dt)
        {
            playerUnitRef.SetVisiblePosition(grid.ConvertTileToScreenPosition(nextPathStep));
            playerUnitRef.SetPosition(finalPath[pathIndex]);
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

        if (playerUnitRef.GetPosition() == tileToMoveTo)
        {
            followingPath = false;
            grid.SetTileOccupation(playerUnitRef.GetPosition(), Occupation::Occupied);
        }
    }
}

void PlayerController::GetPath()
{
    if (!followingPath)
    {
        if (!grid.IsTileOccupied(tileToMoveTo))
        {
            Pathfinder path(grid, playerUnitRef.GetPosition(), tileToMoveTo);
            AStarNode* foundPath = path.FindPath();
            if (foundPath != nullptr)
            {
                int g = foundPath->g;
                std::cout << "foundPath->g: " << g << "\n"
                          << "movementEnergy: " << playerUnitRef.GetMaxEnergy() << "\n"
                          << "availableEnergy: " << playerUnitRef.GetAvailableEnergy() << "\n\n";
                if (g <= playerUnitRef.GetMaxEnergy() && playerUnitRef.GetAvailableEnergy() >= g)
                {
                    playerUnitRef.SpendEnergy(g);
                    finalPath = path.ReconstructPath(foundPath);
                }
                else
                {
                    finalPath.clear();
                }
            
                if (finalPath.size() > 1)
                {
                    pathIndex = 1;
                    maxPathIndex = finalPath.size() - 1;
                }
                else
                {
                    pathIndex = 0;
                    maxPathIndex = 0;
                }
            }
            else
            {
                pathIndex = 0;
                maxPathIndex = 0;
                finalPath.clear();
            }
        }
        else
        {
            pathIndex = 0;
            maxPathIndex = 0;
            finalPath.clear();
        }
    }
}

std::vector<sf::Vector2i> PlayerController::GetFinalPath()
{
    return finalPath;
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
    nextPathStep = finalPath[pathIndex];
}

bool PlayerController::GetFollowingPath()
{
    return followingPath;
}
