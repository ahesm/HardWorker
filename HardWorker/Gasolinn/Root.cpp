#include "Root.h"

#include "Object.h"

HINSTANCE               Root::_hInstance;
HWND                    Root::_hwnd;
POINT                   Root::_mouse;
int                     Root::_sceneWIDTH;
int                     Root::_sceneHEIGHT;

LPDIRECT3D9             Root::_D3D;
LPDIRECT3DDEVICE9       Root::_device;
LPD3DXSPRITE            Root::_sprite;

LPDIRECTINPUT8          Root::_directInput;
LPDIRECTINPUTDEVICE8    Root::_keyboardDevice;
LPDIRECTINPUTDEVICE8    Root::_mouseDevice;
unsigned char           Root::_keyState[256];
DIMOUSESTATE            Root::_mouseState;
IXAudio2               *Root::_xAudio;
IXAudio2MasteringVoice *Root::_xAudioMV;

bool Root::KeyboardCheck(unsigned char keycode)
{
	if (_keyState[keycode] & 0x80)
		return true;
	return false;
}

bool Root::KeyboardCheckRelease(unsigned char keycode)
{
	if (!(_keyState[keycode] & 0x80))
		return true;
	return false;
}