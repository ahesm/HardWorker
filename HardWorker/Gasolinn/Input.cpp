#include "Input.h"

bool Input::_leftDown;
bool Input::_leftUp;
bool Input::_rightDown;
bool Input::_rightUp;
bool Input::_midDown;
bool Input::_midUp;

LRESULT Input::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	_leftDown = false; _leftUp = false; _rightDown = false; _rightUp = false; _midDown = false; _midUp = false;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
		_leftDown = true;
		break;
	case WM_LBUTTONUP:
		_leftUp = true;
		break;

	case WM_RBUTTONDOWN:
		_rightDown = true;
		break;
	case WM_RBUTTONUP:
		_rightUp = true;
		break;

	case WM_MBUTTONDOWN:
		_midDown = true;
		break;
	case WM_MBUTTONUP:
		_midUp = true;
		break;

	default:
		return	DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

bool Input::MouseDown(MouseCode mouse)
{
	if (mouse == MOUSE_LEFT) {
		if (_leftDown) {
			_leftDown = false;
			_leftUp = false;
			return true;
		}
		return false;
	}
	else if (mouse == MOUSE_WHEEL) {
		if (_midDown) {
			_midDown = false;
			_midUp = false;
			return true;
		}
		return false;
	}
	else if (mouse == MOUSE_RIGHT) {
		if (_rightDown) {
			_rightDown = false;
			_rightUp = false;
			return true;
		}
		return false;
	}

	return false;
}

bool Input::MouseUp(MouseCode mouse)
{
	if (mouse == MOUSE_LEFT) {
		if (_leftUp) {
			_leftDown = false;
			_leftUp = false;
			return true;
		}
		return false;
	}
	else if (mouse == MOUSE_WHEEL) {
		if (_midUp) {
			_midDown = false;
			_midUp = false;
			return true;
		}
		return false;
	}
	else if (mouse == MOUSE_RIGHT) {
		if (_rightUp) {
			_rightDown = false;
			_rightUp = false;
			return true;
		}
		return false;
	}

	return false;
}