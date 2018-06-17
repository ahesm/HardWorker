#ifndef _PROGRESS_H_
#define _PROGRESS_H_

#include"Gasolinn.h"

#include<vector>

class IngameMiner;

class SmallThing :public Object
{
public:
	Texture *tRip;
	Texture *tDiamond;
public:
	void Initialize() override{
		tRip = ResourceManager::GetTexture("rip");
		tDiamond = ResourceManager::GetTexture("diamond");
	};
	void Step() override{};
	void Draw() override{
		if (_tag == "rip") DrawTexture(tRip, _x, _y, 0.7, 2, 2, 0, 1);
		if (_tag == "diamond") DrawTexture(tDiamond, _x, _y, 0.7, 2, 2, 0, 1);
	};
	void Destroy() override{};
};

class Progress : public Object
{
public:
	Texture *prog_bar;
	Texture *prog_outline;
	Texture *prog_scale;
	Texture *scale;

	Texture *tamount;
	Texture *tmoney;
	Texture *numbers;

	Texture *btn_return;

	std::vector<IngameMiner*> miners;

	int none_dead;

	bool pd = false;

	float prog_degree;
	float prog_degree_;
	bool return_on;
	bool end;

	float scale_x= 0;

	bool win_once = false;

public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;
};

#endif