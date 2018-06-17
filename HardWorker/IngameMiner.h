#ifndef _INGAMEMINER_H_
#define _INGAMEMINER_H_

#include"Gasolinn.h"

class IngameMiner : public Object
{
public:
	int hp;
	int passion;
	int mineral;
	int advance;
	int tick;
	bool dead;
	Timer *timer;
public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;
};

#endif