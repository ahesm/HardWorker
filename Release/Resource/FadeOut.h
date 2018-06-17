#ifndef _FADEOUT_H_
#define _FADEOUT_H_

#include"Gasolinn.h"

class FadeOut : public Object
{
public:
	Texture *tBlack;
	float alpha;
public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;
};

#endif