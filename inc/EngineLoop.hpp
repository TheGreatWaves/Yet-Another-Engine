#pragma once

#include <SFML/Graphics.hpp>

class Engine
{
public:
    Engine()
        : m_window(sf::VideoMode(800, 600), "My SFML Project")
    {
    }

    void run() noexcept
    {
        while (m_window.isOpen())
        {
            // Update the delta time.
            updateDt();

            // Handle any events (keyboard, mouse, etc.)
            processEvents();

            // Update anything that needs to be updated in real time.
            realTimeUpdate();

            // Update anything that needs to be updated with a fixed timestep.
            fixedTimeUpdate();

            // Render the frame.
            render();
        }
    }

private:

    // Update the delta time (the amount of time since the last frame).
    void updateDt() noexcept
    {
        m_timeSinceLastUpdate = m_clock.restart();
    }

    void processEvents()
    {
        sf::Event event{};
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                m_window.close();
            }
        }
    }

    void update(const sf::Time& dt) noexcept
    {
    }

    void fixedTimeUpdate()
    {
        while (m_timeSinceLastUpdate >= m_timestep)
        {
            m_timeSinceLastUpdate -= m_timestep;
            update(m_timestep);
        }
    }

    void realTimeUpdate() noexcept
    {
        // Stuff that needs to be updated in real time goes here
    }

    void render()
    {
        m_window.clear();

        // Draw your game objects here

        m_window.display();
    }

    sf::RenderWindow m_window;
    sf::Time m_timeSinceLastUpdate;
    const sf::Time m_timestep = sf::seconds(1.f / 144.f);
    sf::Clock m_clock;
};
