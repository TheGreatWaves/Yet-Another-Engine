#pragma once

#include "Common.hpp"
#include <SFML/Window/VideoMode.hpp>

class WindowInfo
{
public:
    // Constructor that initializes the dimensions and title of the window.
    WindowInfo(unsigned int in_width, unsigned int in_height,
        std::string in_title)
        : width_(in_width),
        height_(in_height),
        title_(std::move(in_title)) {}

    // Constructor that initializes the video mode and title of the window.
    WindowInfo(const sf::VideoMode& in_video_mode, std::string in_title)
        : width_(in_video_mode.width),
        height_(in_video_mode.height),
        title_(std::move(in_title)) {}

    // Get the dimensions of the window.
    [[nodiscard]] sf::Vector2u GetDimensions() const
	{
        return { width_, height_ };
    }

    // Get the title of the window.
    [[nodiscard]] const std::string& GetTitle() const { return title_; }

    static WindowInfo Default()
	{
        return { sf::VideoMode::getDesktopMode(), "None" };
    }

private:
    // Dimensions of the window, in pixels.
    unsigned int width_;
    unsigned int height_;

    // Title of the window.
    std::string title_;
};
