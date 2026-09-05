#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "MiniLads");

    window.setFramerateLimit(60); // Set Framerate limit so it runs at same speed on any machine

    sf::Clock deltaClock; // tracks time between frames

    while (window.isOpen())
    {
        float dt = deltaClock.restart().asSeconds(); // calculate delta time

        // Handles events (Input window triggers)
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // Render window
        window.clear();
        window.display();
    }

    return 0;
}