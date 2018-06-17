#include "Minecart.h"

void Minecart::Initialize()
{
	tMinecart = ResourceManager::GetTexture("minecart");
	_tag = "minecart";
	Rect = ResourceManager::GetTexture("rect");
	tMinecart_b = ResourceManager::GetTexture("minecart_body");
	tMinecart_w[0] = ResourceManager::GetTexture("minecar_wheel1");
	tMinecart_w[1] = ResourceManager::GetTexture("minecar_wheel2");
}

void Minecart::Step()
{
	if (isStart && _x < _sceneWIDTH + 1500) {
		acc += 0.015;
		angle_acc += 0.4;
		_speed += acc;
		angle += angle_acc;
	}
}

void Minecart::Draw()
{
	//DrawTexture(tMinecart, _x, _y, 0.1, 2, 2, 0, 1);
	DrawTexture(tMinecart_w[1], _x + 5, _y + 20, 0.1, 2, 2, angle, 1);
	DrawTexture(tMinecart_w[1], _x - 32, _y + 20, 0.1, 2, 2, angle, 1);
	DrawTexture(tMinecart_b, _x, _y-5, 0.1, 2, 2, 0, 1);
	DrawTexture(tMinecart_w[0], _x + 32, _y + 20, 0.1, 2, 2, angle, 1);
	DrawTexture(tMinecart_w[0], _x - 5, _y + 20, 0.1, 2, 2, angle, 1);

//	DrawTexture(tDia, _sceneWIDTH / 2, _sceneHEIGHT / 2, 1, 2, 2, 0, 1);

	SetSamplerStateNone();
}

void Minecart::Destroy()
{

}