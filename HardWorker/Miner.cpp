#include "Miner.h"

#include"Minecart.h"

void Miner::Initialize()
{
	tMiner = ResourceManager::GetTexture("miner");
	auto minecart = _parent->GetInstance("minecart");

	tMiner2 = ResourceManager::GetTexture("miner_expert");
	tMiner3 = ResourceManager::GetTexture("miner_professional");

	dx = _x - minecart->_x;
	_alpha = 0;
	isClicked = false;
	first = true;
	flying = false;
	drag = false;
}

void Miner::Step() 
{
	auto minecart = (Minecart*)_parent->GetInstance("minecart");
	if (minecart->isStart) drag = true;
	if (first)
	{
		_alpha += 0.1;
		if (_alpha >= 1)
			_alpha = 1;
		if (gravity <= 8) {
			_y += gravity;
			gravity += 0.4;
		}
	}
	if(drag) {
		auto minecart = _parent->GetInstance("minecart");
		_x = minecart->_x + dx;
	}
	if (isClicked)
	{
		_alpha -= 0.038f;
		if (_alpha <= 0){
			_alpha = 0;
			DestroyInstance();
			return;
		}
		if (gravity <= 8){
			_y -= gravity;
			gravity += 0.4;
		}
	}
}

void Miner::Draw()
{
	if (_tag == "m_normal")
		DrawTexture(tMiner, _x, _y, _z, 2, 2, 0, _alpha);
	if (_tag == "m_expert")
		DrawTexture(tMiner2, _x, _y, _z, 2, 2, 0, _alpha);
	if (_tag == "m_master")
		DrawTexture(tMiner3, _x, _y, _z, 2, 2, 0, _alpha);
	SetSamplerStateNone();
}

void Miner::Destroy()
{

}