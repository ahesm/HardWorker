#include"FadeIn.h"

#include"GameScene.h"
#include"MineScene.h"
#include"EndMineScene.h"

extern bool start;

void FadeIn::Initialize()
{
	tBlack = ResourceManager::GetTexture("black");
	alpha = 0.0f;
}

void FadeIn::Step()
{
	if (alpha <= 1.0f){
		alpha += 0.0015f;
	}
	if (!start){
		if (alpha >= 0.2f){
			alpha = 1.0f;
			if (_tag == "toMineScene"){
				_parent->ReplaceScene(new MineScene);

			}
			if (_tag == "toGameScene") {
				_parent->ReplaceSceneWithData(new GameScene, ((EndMineScene*)_parent->GetInstance("end"))->data);
				return;
			}
		}
	}
	if (start) alpha += 0.05f;
	if (start&&alpha>=1.0f) _parent->ReplaceScene(new MineScene);
}

void FadeIn::Draw()
{
	DrawTexture(tBlack, _sceneWIDTH / 2, _sceneHEIGHT / 2, 1, 0, alpha);
}

void FadeIn::Destroy()
{

}