#include "GameScene.h"

#include"Progress.h"
#include"IngameMiner.h"
#include"EndGameScene.h"
#include"GameMoney.h"
#include"FadeOut.h"

void GameScene::Initialize()
{
	CreateInstance(new FadeOut);
	CreateInstance(new Progress);
	CreateInstance(new EndGameScene);
	CreateInstance(new GameMoney);
}

void GameScene::Release()
{

}