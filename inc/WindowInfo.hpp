#pragma once

#include "Common.hpp"
#include <SFML/Window/VideoMode.hpp>

class FWindowInfo
{
public:
    // Constructor that initializes the dimensions and title of the window.
    FWindowInfo(unsigned int Width, unsigned int Height, std::string Title)
        : m_dimensions(Width, Height)
        , m_title(std::move(Title))
    {
    }

    // Constructor that initializes the video mode and title of the window.
    FWindowInfo(const sf::VideoMode& VideoMode, std::string Title)
        : m_dimensions(VideoMode.width, VideoMode.height)
        , m_title(std::move(Title))
    {
    }

    // Get the dimensions of the window.
    [[nodiscard]] const sf::Vector2u& GetDimensions() const { return m_dimensions; }

    // Get the title of the window.
    [[nodiscard]] const std::string& GetTitle() const { return m_title; }

    static FWindowInfo Default()
    {
        return { sf::VideoMode::getDesktopMode(), "None" };
    }

private:
    // Dimensions of the window, in pixels.
    sf::Vector2u m_dimensions;

    // Title of the window.
    std::string m_title;
};

