#include "Application.h"

#include "ResourceManager.h"
#include "SoundEngine.h"
#include "Function.h"
#include "Input.h"

Application::Application(ApplicationConfig config)
{
	_CreateWindow(config._title.c_str(), config._width, config._height);
	_sceneWIDTH = config._width;
	_sceneHEIGHT = config._height;

	if (FAILED(_InitializeDirectX()))
	{
		MessageBoxA(_hwnd, "Not initialized.", "Error!", 0);
		return;
	}
}

void Application::Initialize(Scene *firstScene)
{
	Fn::LookupTableCreator();
	_scenes = new Scene *[2];

	firstScene->_super = this;
	firstScene->Initialize();

	_scenes[PREVIOUS] = 0;
	_scenes[CURRENT] = firstScene;

	Run();
}

void Application::Run()
{
	MSG msg;

	ZeroMemory(&msg, sizeof(msg));
	_quit = false;

	int fpsCalcCount = 0;
	DWORD fpsCalcTick = timeGetTime();
	int a = 0;

	while (!_quit)
	{
		_nowTick = timeGetTime();
		if (_oldTick == 0) _oldTick = _nowTick;

		GetCursorPos(&_mouse);
		ScreenToClient(_hwnd, &_mouse);

		_ReadMouse();
		_ReadKeyboard();

		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			_quit = true;
		}
		else
		{
			if (_nowTick >= _oldTick + 1000.0f/120.0f)
			{
				fpsCalcCount += 1;

				_scenes[CURRENT]->Background(_tick);

				_oldTick += 1000.0f / 120.0f;

				if (fpsCalcCount >= 10)
				{

					_fps = 1000.0f * fpsCalcCount / (_nowTick - fpsCalcTick);
					fpsCalcTick = _nowTick;
					fpsCalcCount = 0;
				}
				_tick += 1;
			}
			
	//		printf("%f\n", _fps);
		}
	}

	if (_scenes[PREVIOUS] != NULL)
	{
		for each(auto obj in _scenes[PREVIOUS]->_instances)
		{
			obj.second->Destroy();
		}
		_scenes[PREVIOUS]->Release();
		delete _scenes[PREVIOUS];
	}
	for each(auto obj in _scenes[CURRENT]->_instances)
	{
		obj.second->Destroy();
	}
	_scenes[CURRENT]->Release();
	delete _scenes[CURRENT];

	delete[] _scenes;
}

INT Application::Release()
{
	_ReleaseResource();
	_ReleaseDirectX();
	_DestroyWindow();

	return 0;
}

Scene *Application::GetScene(SCENE_STATE state)
{
	return _scenes[state];
}

void Application::Exit()
{
	_quit = true;
}

void Application::_CreateWindow(const char *title, int width, int height)
{
	_hInstance = GetModuleHandle(NULL);

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, _hInstance, NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL, TEXT("engine"), NULL };
	RegisterClassEx(&wc);

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	_hwnd = CreateWindowA("engine", title, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 50, 50, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, wc.hInstance, NULL);

	ShowWindow(_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(_hwnd);
}

void Application::_DestroyWindow()
{
	DestroyWindow(_hwnd);
	_hwnd = nullptr;

	UnregisterClassA("engine", _hInstance);
	_hInstance = nullptr;
}

HRESULT Application::_InitializeDirectX()
{
	/// DirectX 초기화
	if ((_D3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	/// Device 초기화
	if (FAILED(_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &_device)))
		return E_FAIL;

	/// Sprite 초기화
	if (FAILED(D3DXCreateSprite(_device, &_sprite)))
		return E_FAIL;

	DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&_directInput, NULL);

	_directInput->CreateDevice(GUID_SysKeyboard, &_keyboardDevice, NULL);
	_keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	_keyboardDevice->SetCooperativeLevel(_hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	_keyboardDevice->Acquire();

	_directInput->CreateDevice(GUID_SysMouse, &_mouseDevice, NULL);
	_mouseDevice->SetDataFormat(&c_dfDIMouse);
	_mouseDevice->SetCooperativeLevel(_hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	_mouseDevice->Acquire();

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(XAudio2Create(&_xAudio)))
		return E_FAIL;
	if (FAILED(_xAudio->CreateMasteringVoice(&_xAudioMV))) {
		if (FAILED(_xAudio->CreateMasteringVoice(&_xAudioMV, 2, 44100, 0, 0, NULL))) {
			if (FAILED(_xAudio->CreateMasteringVoice(&_xAudioMV, 2, 48000, 0, 0, NULL))) {
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

void Application::_ReleaseDirectX()
{
	SAFE_RELEASE(_D3D);
	SAFE_RELEASE(_device);
	SAFE_RELEASE(_sprite);

	_xAudioMV->DestroyVoice();
	_xAudioMV = NULL;
	SAFE_RELEASE(_xAudio);
	CoUninitialize();
}

void Application::_ReleaseResource()
{
	for each(auto iterator in ResourceManager::_textures)
		SAFE_RELEASE(iterator.second->_texture);
	ResourceManager::_textures.clear();

	for each(auto iterator in ResourceManager::_shaders)
		SAFE_RELEASE(iterator.second);
	ResourceManager::_shaders.clear();

	ResourceManager::_fonts.clear();

	for each(auto iterator in ResourceManager::_ses) {
		for (int i = 0; i < 5; i++) {
			if (iterator.second != nullptr) {
				iterator.second->_sourceVoice[i]->DestroyVoice();
				iterator.second->_sourceVoice[i] = nullptr;
				delete iterator.second;
				iterator.second = nullptr;
			}
		}
	}

	for each(auto iterator in ResourceManager::_bgms) {
		iterator.second->_sourceVoice->Stop();
	}
	SoundEngine::GetInstance().Destroy();

	ResourceManager::_ses.clear();

}

bool Application::_ReadKeyboard()
{
	HRESULT result;
	result = _keyboardDevice->GetDeviceState(sizeof(_keyState), (LPVOID)&_keyState);

	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			_keyboardDevice->Acquire();
		}
		else
			return false;
	}

	return true;
}

bool Application::_ReadMouse()
{
	HRESULT result;

	result = _mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&_mouseState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			_mouseDevice->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	default:
		return Input::WndProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}