#pragma once

#include <iostream>

#include "SharedContext.hpp"
#include "Core/States/Core/State.hpp"
#include "ECS/ECSUtils.hpp"
#include "ECS/EntityManager.hpp"

#include "Core/States/Impl/TitleState.hpp"


class Engine
{
public:
    Engine()
	    : shared_context_(std::make_unique<Window>(WindowInfo::Default()))
		, statestack_( States::State::Context( shared_context_.window_->GetWindow() ) )
    {
        RegisterStates();
        statestack_.pushState(States::ID::Title);
    }

    void RegisterStates()
    {
        statestack_.registerState<TitleState>(States::ID::Title);
    }

    void Run() noexcept
	{
        while (shared_context_.window_->GetWindow()->isOpen()) 
        {
            // Handle any events (keyboard, mouse, etc.)
            ProcessEvents();

            // Update anything that needs to be updated in real time.
            RealTimeUpdate();

            // Update the delta time.
            UpdateDt();

            // Update anything that needs to be updated with a fixed timestep.
            FixedTimeUpdate();

            // Check the state of the stack, close if empty.
            CheckStack();

            // Render the frame.
            Render();
        }
    }

private:
    // Update the delta time (the amount of time since the last frame).
    void UpdateDt() noexcept
	{
        // time_since_last_update_ = clock_.restart();
    }

    void ProcessEvents()
	{
        sf::Event event{};
        while (shared_context_.window_->GetWindow()->pollEvent(event)) 
        {
            statestack_.handleEvent(event);

            if (event.type == sf::Event::Closed)
                shared_context_.window_->CloseWindow();
        }
    }

    void Update(const sf::Time& dt) noexcept
    {
        statestack_.update(dt);
    }

    void CheckStack() const
    {
        if (statestack_.isEmpty())
        {
            shared_context_.window_->CloseWindow();
        }
    }

    void FixedTimeUpdate()
	{
        time_since_last_update_ = this->clock_.restart();
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
        auto* window = shared_context_.window_->GetWindow();

        window->clear();

        // Draw your game objects here
        statestack_.draw();

        // Reset view
        window->setView(window->getDefaultView());

        // Draw statistics
        // ...

        window->display();
    }

    // Shared context containing a pointer to the window.
    SharedContext       shared_context_;

    sf::Time            time_since_last_update_;
    const sf::Time      timestep_ = sf::seconds(1.f / 144.f);
    sf::Clock           clock_;
    States::StateStack  statestack_;
};
