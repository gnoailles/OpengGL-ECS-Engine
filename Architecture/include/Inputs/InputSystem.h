#pragma once
#include <GLFW/glfw3.h>

class InputSystem
{
public:
	virtual ~InputSystem() = 0;
	static void HandleInputs(GLFWwindow* p_window, int p_key, 
							 int p_scancode, int p_action, int p_mods);
};
