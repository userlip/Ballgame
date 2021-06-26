#include "Headers.h"
extern string input;
void Keyboard::keyboard(int key)
{
	// Taking user input
	switch (key)
	{
	case GLFW_KEY_BACKSPACE:
		if (!input.empty())
		{
			input.pop_back();
		}
	case ' ':
		break;
	default:
		if (input.length() < 17)
		{
			input += key;
		}
		break;
	}
}
