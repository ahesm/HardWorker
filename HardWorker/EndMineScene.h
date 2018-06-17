#ifndef _ENDMINESCENE_H_
#define _ENDMINESCENE_H_

#include"Gasolinn.h"

#include"FadeIn.h"

class EndMineScene : public Object
{
public:
	float acc = 0;
	bool on = false;
	bool ss = false;
	ExtraData *data;
public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;
};

#endif