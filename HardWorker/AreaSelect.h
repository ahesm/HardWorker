#pragma once

#include "Gasolinn.h"

class AreaSelect : public Object
{
public:
	Texture *tMap;
	Texture *Rect;
	ExtraData *data;

	bool rectOn[5];

public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;

};