#include <assert.h>
#include "Mouse.h"
//Mouse::Mouse(GLFWwindow	*_window)
//	: window(_window)
//{
//	assert(_window);
//}

Mouse::Mouse()
{

}

// Use this to read mouse buttons
bool Mouse::GetKeyState(AZUL_MOUSE button)
{
	bool value;

	//if (glfwGetMouseButton(this->window, button) == GLFW_PRESS)
	if (glfwGetMouseButton( button) == GLFW_PRESS)
	{
		value = true;
	}
	else
	{
		value = false;
	}
	
	return value;
}
bool Mouse::IsReleased(AZUL_MOUSE button)
{
	bool value;

	//if (glfwGetMouseButton(this->window, button) == GLFW_PRESS)
	if (glfwGetMouseButton(button) == GLFW_RELEASE)
	{
		value = true;
	}
	else
	{
		value = false;
	}

	return value;
}

void Mouse::GetCursor(float &xPos, float &yPos)
{
	int xDouble;
	int yDouble;

	// get mouse position
	glfwGetMousePos(&xDouble, &yDouble);
	//glfwGetCursorPos(this->window, &xDouble, &yDouble);

	// why the hell would you use a double for a mouse cursor?
	// We went to the moon on 16 bits, why we need 64 for a mouse amazes me

	
	xPos = (float)xDouble;
	yPos = (float)yDouble;

}