#pragma once
#include <SFML/Graphics.hpp>
#include "grid.hpp"

struct AStarNode
{
    sf::Vector2i position; // Where am I?
    int g = 0; // Path cost from start
    int h = 0; // Estimated path cost to destination
    int f = 0; // Final/Total cost of path (g + h)
    AStarNode* pathParent = nullptr; // Where did I come from?
    AStarNode* chainChild = nullptr;
};

class Pathfinder
{
    public:
        Pathfinder(Grid &grid, sf::Vector2i startPoint, sf::Vector2i endPoint);
        ~Pathfinder(); // Destructor, called when object dies, just learned this and it's really cool
        void DoesThisNodeExist(AStarNode* currentNode, sf::Vector2i neighbor);
        void GetNeighbors(AStarNode* currentNode);
        void CalculateGHF(AStarNode* node);
        AStarNode* GetBestNode();
        void CleanUp();

        AStarNode* FindPath();

    private:
        Grid &grid;
        sf::Vector2i startPoint;
        sf::Vector2i endPoint;

        AStarNode* nodeTail = nullptr;
        AStarNode* nodeHead = nullptr;
        std::vector<AStarNode*> openList;
        std::vector<AStarNode*> closedList;
        std::vector<sf::Vector2i> finalPath;
};