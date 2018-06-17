#include "Title.h"

#include"GameScene.h"
#include"MineScene.h"
#include"FadeIn.h"
#include"FadeOut.h"

bool start = true;

void Title::Initialize()
{
	tTitle = ResourceManager::GetTexture("hard_worker");
	tStart = ResourceManager::GetTexture("click_anywhere");
	tBg = ResourceManager::GetTexture("background");

	t_move = 0;
	right = true;
	timer = Timer::Create(_parent);
	show = false;
	
}

void Title::Step()
{
	if (Input::MouseUp(MOUSE_LEFT)){
		//_parent->ReplaceScene(new MineScene);
		_parent->CreateInstanceWithTag(new FadeIn, "toMineScene");
	}
	timer->Start(20, [&]{
		show = !show;
	});
}

void Title::Draw()
{
	DrawTexture(tTitle, _x, _y - 100, 0.2, 1, 1, 0, 1);
	if (show) DrawTexture(tStart, _x, _y + 100-0.5, 0.2, 1.2, 1.2, 0, 1);

	DrawTexture(tBg, t_move , 0, 0, 0, 0, 2, 2, 0, 1);
	if (right)
	{
		t_move -= 0.5;
		if (t_move <= -1469*2+560) right = false;
	}if (!right){
		t_move += 0.5;
		if (t_move >= 0) right = true;
	}
	SetSamplerStateNone();
}	

void Title::Destroy()
{
	
}