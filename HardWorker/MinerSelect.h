#pragma once

#include "Gasolinn.h"
#include<vector>

class Miner;
class MinerSelect : public Object
{
public:
	Texture *tMiner;
	Texture *background;

	Texture *tMiner2;
	Texture *tMiner3;

	Texture *tPlus;

	std::vector<Miner*> miners;

	bool isClick = false;

public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;
};