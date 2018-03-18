#include <Inputs/InputSystem.h>


InputSystem::~InputSystem()
{
}

void InputSystem::HandleInputs(GLFWwindow* p_window, const int key, 
								 int p_scancode, int p_action, int p_mods)
{
	if (key == GLFW_KEY_ESCAPE && p_action == GLFW_PRESS)
		glfwSetWindowShouldClose(p_window, GLFW_TRUE);
}
