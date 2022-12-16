#pragma once

#include "Window.hpp"
#include "ResourceManager.hpp"
#include <memory>

struct SharedContext {
	SharedContext() : window_(nullptr) {}

	std::unique_ptr<Window> window_;
	resources::TextureHolder texture_holder_;
};


