#ifndef __KEYBOARD__
#define __KEYBOARD__
#include "Headers.h"
class Keyboard {
	public:
	static void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods)	  // Callback When key is pressed down
	{
		if(action==GLFW_PRESS) keyboard(key);
	}
	static void keyboard(int);
};
#endif