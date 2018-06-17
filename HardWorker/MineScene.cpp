#include"MineScene.h"

#include "MinerSelect.h"
#include "Minecart.h"
#include "MineEntry.h"
#include"EndMineScene.h"
#include"GameMoney.h"

void MineScene::Initialize()
{
	CreateInstance(new Minecart, _sceneWIDTH / 2 - 160,157*2);
	CreateInstance(new MinerSelect, _sceneWIDTH / 2, _sceneHEIGHT / 2);
	

	CreateInstance(new GameMoney);

	CreateInstance(new MineEntry, 0,0);
	CreateInstance(new EndMineScene);
}

void MineScene::Release()
{

}