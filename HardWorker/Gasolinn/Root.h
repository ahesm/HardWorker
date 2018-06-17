#ifndef _ROOT_H_
#define _ROOT_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <XAudio2.h>
#include <map>
#include <string>

#define SAFE_RELEASE( obj ) \
if (obj != NULL) \
{ \
	obj->Release();\
	obj = nullptr;\
}\

typedef struct Texture
{
	LPDIRECT3DTEXTURE9 _texture;
	int _width, _height;
}Texture;

typedef std::map<std::string, Texture *>     TextureMap;
typedef std::map<std::string, ID3DXEffect *> ShaderMap;
typedef std::map<std::string, std::string>   FontMap;

class Root
{
protected:
	static HINSTANCE               _hInstance;
	static HWND                    _hwnd;
	static POINT                   _mouse;

	static int                     _sceneWIDTH;
	static int                     _sceneHEIGHT;

protected:
	static LPDIRECT3D9             _D3D;
	static LPDIRECT3DDEVICE9       _device;
	static LPD3DXSPRITE            _sprite;

	static LPDIRECTINPUT8          _directInput;
	static LPDIRECTINPUTDEVICE8    _keyboardDevice;
	static LPDIRECTINPUTDEVICE8    _mouseDevice;
	static unsigned char           _keyState[256];
	static DIMOUSESTATE            _mouseState;

	static IXAudio2               *_xAudio;
	static IXAudio2MasteringVoice *_xAudioMV;

	bool KeyboardCheck(unsigned char keycode);
	bool KeyboardCheckRelease(unsigned char keycode);
};

#endif