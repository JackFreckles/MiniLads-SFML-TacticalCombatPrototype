#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include "grid.hpp"
#include "unit.hpp"
#include "playerController.hpp"
#include "pathfinder.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "MiniLads");

    window.setFramerateLimit(60); // Set Framerate limit so it runs at same speed on any machine

    sf::Clock deltaClock; // tracks time between frames

    Grid grid(18, 10);

    Unit playerUnit({0,0});

    PlayerController player(playerUnit, grid);

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

            // detect mouse button presses
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                // check if left was clicked
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    if (grid.GetSelectedTile() == tileMouseIsOn)// && playerUnit.GetVisiblePosition() != grid.ConvertTileToScreenPosition(playerUnit.GetPosition()))
                    {
                        sf::Vector2i currentTile = playerUnit.GetPosition();
                        player.SetTileToMoveTo(tileMouseIsOn);
                        player.GetPath();
                        if (player.GetFoundPath().size() > 0)
                        {
                            player.SetPathStep();
                        }
                        else
                        {
                            player.SetTileToMoveTo(currentTile);
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
        window.display();
    }

    return 0;
}