#pragma once

#include "Window.hpp"
#include <memory>

struct FSharedContext
{
	FSharedContext()
		: m_window(nullptr)
	{}

	std::unique_ptr<FWindow> m_window;
};

