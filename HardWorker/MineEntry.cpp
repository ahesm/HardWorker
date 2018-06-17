#include "MineEntry.h"

int day = 0;

void MineEntry::Initialize()
{
	tMineEntry = ResourceManager::GetTexture("mine_back");
	tDay = ResourceManager::GetTexture("day");
	numbers = ResourceManager::GetTexture("number_black");
}

void MineEntry::Step()
{

}

void MineEntry::Draw()	
{
	DrawTexturePart(tMineEntry, _x, _y, 0, 0, 0, 232, 200, 0,0, 2, 2, 0, 1);
	DrawTexturePart(tMineEntry, _x+232*2, _y, 0.2, 232, 0, 560-232, 200,0,0, 2, 2, 0, 1);

	DrawTexture(tDay, _sceneWIDTH - 100,7.5, 0.7,0,0,2,2,0, 1);
	DrawNumber(numbers,day,6, _sceneWIDTH-30, 15 , 0.9, 2,2, 1, 0);
}

void MineEntry::Destroy()
{

}
