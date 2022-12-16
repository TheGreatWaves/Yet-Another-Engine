#pragma once

#include "WindowInfo.hpp"
class Window {
public:
    // Constructor that initializes the window with the dimensions and title specified in the window info object.
    explicit Window(const WindowInfo& in_window_info)
        : window_(sf::VideoMode(in_window_info.GetDimensions().x,
            in_window_info.GetDimensions().y),
            in_window_info.GetTitle()),
        window_info_(in_window_info) {}

    // Update the SFML window with the dimensions and title specified in the window info object.
    void UpdateWindow()
	{
        window_.setSize(window_info_.GetDimensions());
        window_.setTitle(window_info_.GetTitle());
    }

    // Check if the window is open.
    [[nodiscard]] bool IsOpen() const { return window_.isOpen(); }

    // Get a pointer to the SFML window.
    sf::RenderWindow* GetWindow() { return &window_; }

    // Set the view to be used for rendering.
    void SetView(const sf::View& in_view) { window_.setView(in_view); }

    // Set the viewport for the window.
    void SetViewport(const sf::FloatRect& in_viewport)
	{
        // Create a new view and use it.
        SetView(sf::View{ in_viewport });
    }

private:
    // The SFML window.
    sf::RenderWindow window_;

    // Information about the window.
    WindowInfo window_info_;
};
