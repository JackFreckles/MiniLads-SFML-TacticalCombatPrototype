#include "pathfinder.hpp"

Pathfinder::Pathfinder(Grid &grid, sf::Vector2i startPoint, sf::Vector2i endPoint) 
: grid(grid), startPoint(startPoint), endPoint(endPoint)
{
    nodeHead = new AStarNode;
    nodeHead->position = startPoint;

    nodeTail = nodeHead;
    openList.push_back(nodeHead);
}

Pathfinder::~Pathfinder()
{
    CleanUp();
}

void Pathfinder::DoesThisNodeExist(AStarNode* currentNode, sf::Vector2i neighbor)
{
    auto it = std::find_if(openList.begin(), openList.end(), [neighbor](const AStarNode* n)
    {
        return n != nullptr && n->position == neighbor;
    });

    if (it != openList.end())
    {
        AStarNode* tempParent = (*it)->pathParent;
        int tempG = (*it)->g;
        int tempF = (*it)->f;
        int tempH = (*it)->h;
        (*it)->pathParent = currentNode;
        CalculateGHF(*it);

        if ((*it)->g < tempG)
        {
            ;
        }
        else
        {
            (*it)->pathParent = tempParent;
            (*it)->g = tempG;
            (*it)->f = tempF;
            (*it)->h = tempH;
        }
    }
    else
    {
        auto it2 = std::find_if(closedList.begin(), closedList.end(), [neighbor](const AStarNode* n)
        {
            return n != nullptr && n->position == neighbor;
        });

        if (it2 != closedList.end())
        {
            ;
        }
        else
        {
            AStarNode* node = new AStarNode;
            node->position = neighbor;
            node->pathParent = currentNode;
            CalculateGHF(node);
            nodeTail->chainChild = node;
            nodeTail = node;
            openList.push_back(nodeTail);
        }
    }
}

void Pathfinder::GetNeighbors(AStarNode* currentNode)
{
    sf::Vector2i leftNeighbor{currentNode->position.x - 1, currentNode->position.y};
    sf::Vector2i rightNeighbor{currentNode->position.x + 1, currentNode->position.y};
    sf::Vector2i upNeighbor{currentNode->position.x, currentNode->position.y - 1};
    sf::Vector2i downNeighbor{currentNode->position.x, currentNode->position.y + 1};

    if (grid.IsValidTile(leftNeighbor) && grid.IsTileWalkable(leftNeighbor))
    {
        DoesThisNodeExist(currentNode, leftNeighbor);
    }
    if (grid.IsValidTile(rightNeighbor) && grid.IsTileWalkable(rightNeighbor))
    {
        DoesThisNodeExist(currentNode, rightNeighbor);
    }
    if (grid.IsValidTile(upNeighbor) && grid.IsTileWalkable(upNeighbor))
    {
        DoesThisNodeExist(currentNode, upNeighbor);
    }
    if (grid.IsValidTile(downNeighbor) && grid.IsTileWalkable(downNeighbor))
    {
        DoesThisNodeExist(currentNode, downNeighbor);
    }
}

void Pathfinder::CalculateGHF(AStarNode* node)
{
    if (node->pathParent != nullptr)
    {
        if (grid.GetTileType(node->position) == TileType::Grass || grid.GetTileType(node->position) == TileType::Dirt)
        {
            node->g = std::abs(node->position.x - node->pathParent->position.x) + std::abs(node->position.y - node->pathParent->position.y) + node->pathParent->g; // path cost from start using previous g as reference
        }

        if (grid.GetTileType(node->position) == TileType::Mud)
        {
            node->g = std::abs(node->position.x - node->pathParent->position.x) + std::abs(node->position.y - node->pathParent->position.y) + node->pathParent->g + 1; // path cost from start using previous g as reference
        }
    }
    else
    {
        node->g = -1;
    }
    node->h = std::abs(node->position.x - endPoint.x) + std::abs(node->position.y - endPoint.y); // Estimated path cost from to destination
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

AStarNode* Pathfinder::FindPath()
{
    AStarNode* currentPathTail = nodeHead;
    while (currentPathTail->position != endPoint)
    {
        currentPathTail = GetBestNode();
        if (currentPathTail != nullptr)
        {
            closedList.push_back(currentPathTail);
            std::erase(openList, currentPathTail);
            GetNeighbors(currentPathTail);
        }
        else
        {
            return nullptr; // No path found
        }
    }

    return currentPathTail;
}