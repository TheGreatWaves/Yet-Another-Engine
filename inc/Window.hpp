#pragma once

#include "WindowInfo.hpp"

class FWindow
{
public:
    // Constructor that initializes the window with the dimensions and title specified in the window info object.
    explicit FWindow(const FWindowInfo& WindowInfo)
        : m_window(sf::VideoMode(WindowInfo.GetDimensions().x, WindowInfo.GetDimensions().y), WindowInfo.GetTitle())
        , m_windowInfo(WindowInfo)
    {
    }

    // Update the SFML window with the dimensions and title specified in the window info object.
    void UpdateWindow()
    {
        m_window.setSize(m_windowInfo.GetDimensions());
        m_window.setTitle(m_windowInfo.GetTitle());
    }

    // Check if the window is open.
    [[nodiscard]] bool IsOpen() const { return m_window.isOpen(); }

    // Get a pointer to the SFML window.
    sf::RenderWindow* GetWindow() { return &m_window; }

    // Set the view to be used for rendering.
    void SetView(const sf::View& View) { m_window.setView(View); }

    // Set the viewport for the window.
    void SetViewport(const sf::FloatRect& Viewport)
    {
        // Create a new view and use it.
        SetView(sf::View{ Viewport });
    }

private:
    // The SFML window.
    sf::RenderWindow m_window;

    // Information about the window.
    FWindowInfo m_windowInfo;
};

