#include "Surface.h"
#include "utils.h"
#include "Window.h"

namespace Horizon {

	Surface::Surface(std::shared_ptr<Instance> instance, std::shared_ptr<Window> window) :mInstance(instance), mWindow(window)
	{
		createSurface();
	}

	Surface::~Surface()
	{
		vkDestroySurfaceKHR(mInstance->get(), mSurface, nullptr);
	}

	VkSurfaceKHR Surface::get() const
	{
		return mSurface;
	}

	void Surface::createSurface()
	{
		printVkError(glfwCreateWindowSurface(mInstance->get(), mWindow->getWindow(), nullptr, &mSurface), "create surface");
	}
}