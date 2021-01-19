#pragma once
#include "Display.h"
#include "../AncientArcher.h"
namespace AA
{
class DisplayCallbacks 
{
friend class AncientArcher;
private:
	static void perspectiveMouseCallback(GLFWwindow * window, double xpos, double ypos)
	{
		Engine->PerspectiveMouseHandler(window, (float)xpos, (float)ypos);
	}
	static void standardMouseCallback(GLFWwindow * window, double xpos, double ypos)
	{
		Engine->StandardMouseHandler(window, (float)xpos, (float)ypos);
	}
	static void scrollCallback(GLFWwindow * window, double xpos, double ypos)
	{
		Engine->ScrollHandler(window, (float)xpos, (float)ypos);
	}
	static void reshapeCallback(GLFWwindow * window, int w, int h)
	{
		Engine->ReshapeWindowHandler(window, w, h);
	}
};
}  //end namespace AA