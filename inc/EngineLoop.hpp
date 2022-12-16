#pragma once

#include <iostream>

#include "SharedContext.hpp"
#include "ECS/ECSUtils.hpp"
#include "ECS/EntityManager.hpp"

class Engine
{
public:
    Engine()
	{
        shared_context_.window_ =
            std::make_unique<Window>(WindowInfo::Default());
    }

    void Run() noexcept
	{
        while (shared_context_.window_->GetWindow()->isOpen()) 
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
        time_since_last_update_ = clock_.restart();
    }

    void ProcessEvents()
	{
        sf::Event event{};
        while (shared_context_.window_->GetWindow()->pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape)) 
            {
                shared_context_.window_->GetWindow()->close();
            }
        }
    }

    void Update(const sf::Time& dt) noexcept
    {
	    
    }

    void FixedTimeUpdate()
	{
        while (time_since_last_update_ >= timestep_) 
        {
            time_since_last_update_ -= timestep_;
            Update(timestep_);
        }
    }

    void RealTimeUpdate() noexcept
	{
        // Stuff that needs to be updated in real time goes here
    }

    void Render()
	{
        shared_context_.window_->GetWindow()->clear();

        // Draw your game objects here

        shared_context_.window_->GetWindow()->display();
    }

    // Shared context containing a pointer to the window.
    SharedContext shared_context_;

    sf::Time time_since_last_update_;
    const sf::Time timestep_ = sf::seconds(1.f / 144.f);
    sf::Clock clock_;

};
