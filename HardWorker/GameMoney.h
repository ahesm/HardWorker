#ifndef _GAMEMONEY_H_
#define _GAMEMONEY_H_

#include"Gasolinn.h"

class GameMoney : public Object
{

public:
	Texture* numbers;
	Texture* symbol;

	Texture *tDia;

	Texture *clear;
	Texture *hire;
	Texture *ret;
	Texture *earn;
	Texture *total;

	Texture *rect;

	float show_dialog;
	bool show_on = false;
	bool show_off = false;
	bool cleared;
public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;
};

#endif