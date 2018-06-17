#ifndef _ENDGAMESCENE_H_
#define _ENDGAMESCENE_H_

#include"Gasolinn.h"

#include<vector>

typedef struct _mine{
public:
	float _x, _y;
	float alpha = 1.0f;
	char* tag;
}_mine;

class EndGameScene : public Object
{

public:
	Texture *background;
	Texture *mineEntry;
	Texture *tMinecart_b;
	Texture *tMinecart_w[2];
	Texture *tMiner;
	Texture *tSMiner;
	Texture *tMiner2;
	Texture *tSMiner2;
	Texture *tMiner3;
	Texture *tSMiner3;
	Texture *tDay;
	Texture *numbers;
	float acc = 0;
	float acc2 = 0;

	float angle = 0;
	float angle_acc = 0;

	bool angle_s = false;
	bool out = false;

	float cart_x, cart_y;

	bool once = true;

	bool flying = false;
	float gravity = 0.0f;
	float alpha = 1.0f;

	std::vector<_mine*> _mines;
public:
	void Initialize() override;
	void Step() override;
	void Draw() override;
	void Destroy() override;
};

#endif