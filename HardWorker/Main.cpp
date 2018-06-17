#include "Gasolinn.h"

#include "MainMenu.h"
#include "MineScene.h"
#include"GameScene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lp, INT nShow)
{
	ApplicationConfig config("Hard Worker", 560,400);

	Application app(config);

	config.MakeTextureMap("Resource\\Texture", "Texture", "Resource\\");
	config.LoadTextureMap("Resource\\Texture.map");

	config.MakeFontMap("Resource\\Font", "Font", "Resource\\");
	config.LoadFontMap("Resource\\Font.map");

	config.MakeSEMap("Resource\\SE", "SE", "Resource\\");
	config.LoadSEMap("Resource\\SE.map");

	app.Initialize(new MainMenu);

	return app.Release();
}