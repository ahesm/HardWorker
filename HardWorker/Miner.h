#pragma once

#include "Gasolinn.h"

class Miner : public Object
{
public:
	Texture *tMiner;
	Texture *tMiner2;
	Texture *tMiner3;

	float gravity = 0;

	bool isClicked;
	bool first;

	bool flying;
	bool drag;

	int dx, dy;


public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;

};