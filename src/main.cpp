#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include "grid.hpp"
#include "unit.hpp"
#include "playerController.hpp"
#include "pathfinder.hpp"
#include "turnSystem.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "MiniLads");

    window.setFramerateLimit(60); // Set Framerate limit so it runs at same speed on any machine

    sf::Clock deltaClock; // tracks time between frames

    Grid grid(18, 10);

    Unit playerUnit({0,0}, 10, UnitClass::Knight, UnitType::Player);
    grid.SetTileOccupation(playerUnit.GetPosition(), Occupation::Occupied);
    Unit enemyUnit({5,5}, 0, UnitClass::Barbarian, UnitType::Enemy);
    enemyUnit.SetVisiblePosition(grid.ConvertTileToScreenPosition(enemyUnit.GetPosition()));
    grid.SetTileOccupation({5,5}, Occupation::Occupied);

    PlayerController player(playerUnit, grid);

    TurnSystem turnSystem(playerUnit, enemyUnit);

    std::cout << "MiniLads Window has successfully opened!\n\n";

    while (window.isOpen())
    {
        float dt = deltaClock.restart().asSeconds(); // calculate delta time

        sf::Vector2i tileMouseIsOn = grid.GetTileAtMouse(window); // gets the specific tile the mouse is on
        
        // Handles events (Input window triggers)
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            switch (turnSystem.GetWhoseTurn())
            {
                case (TurnState::PlayerTurn):
                {
                    // detect mouse button presses
                    if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
                    {
                        // check if left was clicked
                        if (mousePressed->button == sf::Mouse::Button::Left)
                        {
                            if (grid.GetSelectedTile() == tileMouseIsOn)
                            {
                                if (!player.GetFollowingPath())
                                {
                                    sf::Vector2i currentTile = playerUnit.GetPosition();
                                    player.SetTileToMoveTo(tileMouseIsOn);
                                    player.GetPath();
                                    if (player.GetFinalPath().size() > 0)
                                    {
                                        grid.SetTileOccupation(currentTile, Occupation::Unoccupied);
                                        player.SetPathStep();
                                    }
                                    else
                                    {
                                        player.SetTileToMoveTo(currentTile);
                                    }
                                }
                            }
                            else
                            {
                                grid.SetSelectedTile(tileMouseIsOn);
                                if (!grid.IsTileWalkable(tileMouseIsOn))
                                {
                                    std::cout << "This is an unwalkable tile\n";
                                }
                            }
                        }

                        if (mousePressed->button == sf::Mouse::Button::Right)
                        {
                            grid.SetSelectedTile(tileMouseIsOn);
                            if (grid.IsTileOccupied(grid.GetSelectedTile()))
                            {
                                std::cout << "tile: (" << grid.GetSelectedTile().x << "," << grid.GetSelectedTile().y << ") is occupied\n";
                            }
                        }
                    }
                    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                    {
                        if (keyPressed->code == sf::Keyboard::Key::Q)
                        {
                            turnSystem.EndTurn();
                            std::cout << "Player turn ended \n";
                        }
                    }
                    break;
                }
                case (TurnState::EnemyTurn):
                {
                    turnSystem.EndTurn();
                    std::cout << "Enemy turn ended \n";
                    break;
                }
            }
        }
        
        // Render window
        window.clear();
        grid.DrawGrid(window);
        grid.HighlightHoveredTile(window, tileMouseIsOn); // highlights the tile that is currently hovered over
        if (playerUnit.GetVisiblePosition() != grid.ConvertTileToScreenPosition(player.GetTileToMoveTo()))
        {
            player.SlideToNewTile(dt);
        }
        playerUnit.Draw(window, playerUnit.GetVisiblePosition());
        enemyUnit.Draw(window, enemyUnit.GetVisiblePosition());
        window.display();
    }

    return 0;
}