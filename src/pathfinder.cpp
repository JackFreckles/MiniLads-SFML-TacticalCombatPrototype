#include "pathfinder.hpp"

Pathfinder::Pathfinder(Grid &grid, sf::Vector2i startPoint, sf::Vector2i endTile) 
: grid(grid), startPoint(startPoint), endTile(endTile)
{
    nodeHead = new AStarNode;
    nodeHead->position = startPoint;
    nodeHead->g = 0;
    nodeHead->h = 0;
    nodeHead->f = 0;

    nodeTail = nodeHead;
}

Pathfinder::~Pathfinder()
{
    CleanUp();
}

void Pathfinder::GetNeighbors(AStarNode* currentNode)
{
    sf::Vector2i leftNeighbor{currentNode->position.x - 1, currentNode->position.y};
    sf::Vector2i rightNeighbor{currentNode->position.x + 1, currentNode->position.y};
    sf::Vector2i upNeighbor{currentNode->position.x, currentNode->position.y - 1};
    sf::Vector2i downNeighbor{currentNode->position.x, currentNode->position.y + 1};

    if (grid.IsValidTile(leftNeighbor) && grid.IsTileWalkable(leftNeighbor))
    {
        AStarNode* node = new AStarNode;
        node->position = leftNeighbor;
        node->pathParent = currentNode;
        CalculateGHF(node);
        nodeTail->chainChild = node;
        nodeTail = node;
        openList.push_back(nodeTail);
    }
    if (grid.IsValidTile(rightNeighbor) && grid.IsTileWalkable(rightNeighbor))
    {
        AStarNode* node = new AStarNode;
        node->position = rightNeighbor;
        node->pathParent = currentNode;
        CalculateGHF(node);
        nodeTail->chainChild = node;
        nodeTail = node;
        openList.push_back(nodeTail);
    }
    if (grid.IsValidTile(upNeighbor) && grid.IsTileWalkable(upNeighbor))
    {
        AStarNode* node = new AStarNode;
        node->position = upNeighbor;
        node->pathParent = currentNode;
        CalculateGHF(node);
        nodeTail->chainChild = node;
        nodeTail = node;
        openList.push_back(nodeTail);
    }
    if (grid.IsValidTile(downNeighbor) && grid.IsTileWalkable(downNeighbor))
    {
        AStarNode* node = new AStarNode;
        node->position = downNeighbor;
        node->pathParent = currentNode;
        CalculateGHF(node);
        nodeTail->chainChild = node;
        nodeTail = node;
        openList.push_back(nodeTail);
    }
}

void Pathfinder::CalculateGHF(AStarNode* node)
{
    if (node->pathParent != nullptr)
    {
        node->g = std::abs(node->position.x - node->pathParent->position.x) + std::abs(node->position.y - node->pathParent->position.y) + node->pathParent->g; // path cost from start using previous g as reference
    }
    else
    {
        node->g = -1;
    }
    node->h = std::abs(node->position.x - endTile.x) + std::abs(node->position.y - endTile.y); // Estimated path cost from to destination
    node->f = node->g + node->h; // Final/Total cost of path (g + h)
}

AStarNode* Pathfinder::GetBestNode()
{
    if (openList.size() != 0)
    {
        AStarNode* bestNode = openList[0];
        for (int i = 0; i < openList.size(); i++)
        {
            if (openList[i]->f < bestNode->f)
            {
                bestNode = openList[i];
            }
        }

        return bestNode;
    }
    else
    {
        return nullptr;
    }
}

void Pathfinder::CleanUp()
{
    while (nodeHead != nullptr)
    {
        AStarNode* tempHead = nodeHead->chainChild;
        delete nodeHead;
        nodeHead = tempHead;
    }

    nodeTail = nullptr;
    nodeHead = nullptr;
    openList.clear();
    closedList.clear();
}