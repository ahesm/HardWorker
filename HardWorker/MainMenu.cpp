#include "MainMenu.h"

#include "Title.h"

void MainMenu::Initialize()
{
	CreateInstance(new Title, _sceneWIDTH / 2, _sceneHEIGHT / 2);
}

void MainMenu::Release()
{

}