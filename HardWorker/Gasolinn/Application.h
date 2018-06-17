#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//#include <vector>
#include <d3d9.h>
#include <d3dx9.h>

#include "ApplicationConfig.h"
#include "Scene.h"

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")
#pragma comment(lib, "dinput8")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "winmm")

#if _DEBUG
#pragma comment(lib, "libogg_d")
#pragma comment(lib, "libvorbis_d")
#pragma comment(lib, "libvorbisfile_d")
#else
#pragma comment(lib, "libogg")
#pragma comment(lib, "libvorbis")
#pragma comment(lib, "libvorbisfile")
#endif

enum SCENE_STATE
{
	PREVIOUS, CURRENT
};

class Application : public Root
{
public:
	Scene **_scenes;

	float _fps;

	DWORD _oldTick;
	DWORD _nowTick;

	DWORD _tick = 0;

	bool _quit = false;

public:
	Application(ApplicationConfig config);

	void Initialize(Scene *firstScene);

	void Run();

	INT Release();

public:
	Scene *GetScene(SCENE_STATE state);
	void Exit();

private:
	void _CreateWindow(const char *title, int width, int height);
	void _DestroyWindow();

	HRESULT _InitializeDirectX();
	void _ReleaseDirectX();

	void _ReleaseResource();

	bool _ReadKeyboard();
	bool _ReadMouse();
};

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif