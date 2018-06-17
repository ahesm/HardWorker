#include "AreaSelect.h"

#include"GameScene.h"

void AreaSelect::Initialize()
{
	tMap = ResourceManager::GetTexture("africa_map");
	Rect = ResourceManager::GetTexture("rect");
	data = new ExtraData;

	for (int i = 0; i < 5; i++) rectOn[0] = false;
}

void AreaSelect::Step()
{
	int region;
	bool clicked = false;
	if (Input::MouseUp(MOUSE_LEFT))
	{
		if (Fn::CollisionWithMouse(_mouse, 300, 180, 170, 90) || Fn::CollisionWithMouse(_mouse, 260, 130, 50, 30)){
			rectOn[0] = true;
			region = 0; clicked = true;
		}
		else rectOn[0] = false;
		if (Fn::CollisionWithMouse(_mouse, 390, 93, 200, 80)){
			rectOn[1] = true;
			region = 1; clicked = true;
		}
		else rectOn[1] = false;
		if (Fn::CollisionWithMouse(_mouse, 445, 180, 120, 60) || Fn::CollisionWithMouse(_mouse, 430, 255, 85, 85)) {
			rectOn[2] = true;
			region = 2; clicked = true;
		}
		else rectOn[2] = false;
		if (Fn::CollisionWithMouse(_mouse, 518, 276, 90, 130)){
			rectOn[3] = true;
			region = 3; clicked = true;
		}
		else rectOn[3] = false;
		if (Fn::CollisionWithMouse(_mouse, 420, 360, 90, 120)){
			rectOn[4] = true;
			region = 4; clicked = true;
		}
		else rectOn[4] = false;
	}
	if (clicked){
		data->PutData(region, "region");
		ReplaceSceneWithData(new GameScene, data);
	}
}

void AreaSelect::Draw()
{
	DrawTexture(tMap, _x , _y, _z, 2, 2, 0, 1);
	if (rectOn[0]){
		DrawTexture(Rect, 300, 180, _z, 170, 90, 0, 1);
		DrawTexture(Rect, 260, 130, _z, 50, 30, 0, 1);
	}
	if (rectOn[1]) DrawTexture(Rect, 390, 93, _z, 200, 80, 0, 1);
	if (rectOn[2]){ 
		DrawTexture(Rect, 445, 180, _z, 120, 60, 0, 1); 
		DrawTexture(Rect, 430, 255, _z, 85, 85, 0, 1);
	}
	if(rectOn[3]) DrawTexture(Rect, 518, 276, _z, 90, 130, 0, 1);
	if(rectOn[4]) DrawTexture(Rect, 420, 360, _z, 90, 120, 0, 1);
	SetSamplerStateNone();
}

void AreaSelect::Destroy()
{

}