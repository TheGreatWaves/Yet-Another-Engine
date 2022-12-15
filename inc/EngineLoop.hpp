#pragma once

#include "SharedContext.hpp"

class FEngine
{
public:
    FEngine()
    {
        m_sharedContext.m_window = std::make_unique<FWindow>(
            FWindowInfo::Default()
            );
    }

    void Run() noexcept
    {
        while (m_sharedContext.m_window->GetWindow()->isOpen())
        {
            // Update the delta time.
            UpdateDt();

            // Handle any events (keyboard, mouse, etc.)
            ProcessEvents();

            // Update anything that needs to be updated in real time.
            RealTimeUpdate();

            // Update anything that needs to be updated with a fixed timestep.
            FixedTimeUpdate();

            // Render the frame.
            Render();
        }
    }

private:

    // Update the delta time (the amount of time since the last frame).
    void UpdateDt() noexcept
    {
        m_timeSinceLastUpdate = m_clock.restart();
    }

    void ProcessEvents()
    {
        sf::Event Event{};
        while (m_sharedContext.m_window->GetWindow()->pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed ||
                (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape))
            {
                m_sharedContext.m_window->GetWindow()->close();
            }
        }
    }

    void Update(const sf::Time& Dt) noexcept
    {
    }

    void FixedTimeUpdate()
    {
        while (m_timeSinceLastUpdate >= m_timestep)
        {
            m_timeSinceLastUpdate -= m_timestep;
            Update(m_timestep);
        }
    }

    void RealTimeUpdate() noexcept
    {
        // Stuff that needs to be updated in real time goes here
    }

    void Render()
    {
        m_sharedContext.m_window->GetWindow()->clear();

        // Draw your game objects here

        m_sharedContext.m_window->GetWindow()->display();
    }

    // Shared context containing a pointer to the window.
    FSharedContext m_sharedContext;

    sf::Time m_timeSinceLastUpdate;
    const sf::Time m_timestep = sf::seconds(1.f / 144.f);
    sf::Clock m_clock;
};
