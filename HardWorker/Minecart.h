#pragma once

#include "Gasolinn.h"

class Minecart : public Object
{
public:
	Texture *tMinecart;

	Texture *tMinecart_b;
	Texture *tMinecart_w[2];

	Texture *Rect;
//	Texture *tDia;

	float angle = 0;
	float angle_acc = 0;
	int count_miner = 0;
	int count_miner2 = 0;
	int count_miner3 = 0;
	bool isStart = false;
	float acc = 0;
public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;
};