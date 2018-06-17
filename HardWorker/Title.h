#pragma once

#include "Gasolinn.h"

class Title : public Object
{
public:
	Texture *tTitle;
	Texture *tStart;
	Texture *tBg;
	Texture *tWhite;

	bool isStart = false;

	float t_move;
	bool right;
	bool show;
	Timer *timer;

public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;
};