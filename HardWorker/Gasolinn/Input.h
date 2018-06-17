#ifndef _INPUT_H_
#define _INPUT_H_

#include "Root.h"

typedef enum _MouseCode
{
	MOUSE_LEFT = 0, MOUSE_RIGHT = 1, MOUSE_WHEEL = 2,
}MouseCode;

class Input : public Root
{
private:
	static bool _leftDown;
	static bool _leftUp;

	static bool _rightDown;
	static bool _rightUp;

	static bool _midDown;
	static bool _midUp;

public:
	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static bool MouseDown(MouseCode mouse);
	static bool MouseUp(MouseCode mouse);
};

#endif