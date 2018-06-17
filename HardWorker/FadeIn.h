#ifndef _FADEIN_H_
#define _FADEIN_H_

#include"Gasolinn.h"

class FadeIn : public Object
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