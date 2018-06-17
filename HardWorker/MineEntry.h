#pragma once

#include "Gasolinn.h"


class MineEntry : public Object
{
public:
	Texture *tMineEntry;
	Texture *tDay;
	Texture *numbers;
public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;

};