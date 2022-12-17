#pragma once

#include "Window.hpp"
#include "ResourceManager.hpp"
#include <memory>

struct SharedContext {
	SharedContext() : window_(nullptr) {}

	SharedContext(std::unique_ptr<Window> window) : window_(std::move(window)) {};

	std::unique_ptr<Window> window_;
	resources::TextureHolder texture_holder_;
};


