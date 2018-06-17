#include "MinerSelect.h"

#include "Miner.h"
#include "Minecart.h"
#include"FadeOut.h"

extern int money;
extern int amount;
extern bool changed;
extern bool failed;

extern int hire_score;
extern int earn_score;

extern bool start;

void MinerSelect::Initialize()
{
	tMiner = ResourceManager::GetTexture("poster_worker");
	tMiner2 = ResourceManager::GetTexture("poster_expert");
	tMiner3 = ResourceManager::GetTexture("poster_professional");
	tPlus = ResourceManager::GetTexture("plus");
}

void MinerSelect::Step()
{
	if (start){
		_parent->CreateInstance(new FadeOut);
		start = false;
	}
	if (changed){
		if (!failed){
			money += amount;
			earn_score = amount;
		}failed = false;
		changed = false;
	}
	if (_mouseState.rgbButtons[0] && !isClick) {
		Minecart *minecart = (Minecart *)_parent->GetInstance("minecart");
		if (Fn::CollisionWithMouse(_mouse, _x - 220, _y - 114, tMiner->_width * 2, tMiner->_height * 2)) {
			if (minecart->count_miner + minecart->count_miner2 + minecart->count_miner3 <= 5 && money >= 100) {
				SoundEngine::GetInstance().PlaySE("click", false);
				money -= 100;
				hire_score += 100;
				minecart->count_miner += 1;
				miners.push_back(new Miner);
				_parent->CreateInstanceWithTag(miners[miners.size()-1], minecart->_x + Random::rand.NextInt(minecart->tMinecart->_width*2-48) - minecart->tMinecart->_width+24, minecart->_y - Random::rand.NextInt(15) - 100,"m_normal");
			}
			isClick = true;
		}
		if (Fn::CollisionWithMouse(_mouse, _x - 140, _y - 114, tMiner->_width * 2, tMiner->_height * 2)) {
			if (minecart->count_miner + minecart->count_miner2 + minecart->count_miner3 <= 5 && money >= 500) {
				SoundEngine::GetInstance().PlaySE("click", false);
				money -= 500;
				hire_score += 500;
				minecart->count_miner2 += 1;
				miners.push_back(new Miner);
				_parent->CreateInstanceWithTag(miners[miners.size() - 1], minecart->_x + Random::rand.NextInt(minecart->tMinecart->_width * 2 - 48) - minecart->tMinecart->_width + 24, minecart->_y - Random::rand.NextInt(15) - 100, "m_expert");
			}
			isClick = true;
		}
		if (Fn::CollisionWithMouse(_mouse, _x - 60, _y - 114, tMiner->_width * 2, tMiner->_height * 2)) {
			if (minecart->count_miner + minecart->count_miner2 + minecart->count_miner3 <= 5 && money >= 2000) {
				SoundEngine::GetInstance().PlaySE("click", false);
				money -= 2000;
				hire_score += 2000;
				minecart->count_miner3 += 1;
				miners.push_back(new Miner);
				_parent->CreateInstanceWithTag(miners[miners.size() - 1], minecart->_x + Random::rand.NextInt(minecart->tMinecart->_width * 2 - 48) - minecart->tMinecart->_width + 24, minecart->_y - Random::rand.NextInt(15) - 100, "m_master");
			}
			isClick = true;
		}

		if (Fn::CollisionWithMouse(_mouse,minecart->_x, minecart->_y, minecart->tMinecart->_width * 2, minecart->tMinecart->_height * 2) && minecart->count_miner + minecart->count_miner2
			+minecart->count_miner3 != 0)
		{
			minecart->isStart = true;
		}

		for (int i = miners.size() -1; i > -1; i--){
			if (Fn::CollisionWithMouse(_mouse, miners[i]->_x, miners[i]->_y, tMiner->_width * 2, tMiner->_height * 2) && !miners[i]->flying)
			{
				if (!minecart->isStart){
					miners[i]->isClicked = true;
					miners[i]->first = false;
					miners[i]->flying = true;
					miners[i]->gravity = 0;
					if (miners[i]->_tag == "m_normal"){
						minecart->count_miner -= 1;
						money += 100;
						hire_score -= 100;
					}
					else if (miners[i]->_tag == "m_expert"){
						minecart->count_miner2 -= 1;
						money += 500;
						hire_score -= 500;
					}
					else if (miners[i]->_tag == "m_master"){
						minecart->count_miner3 -= 1;
						money += 2000;
						hire_score -= 2000;
					}
					isClick = true;
					break;
				}
			}
		}
	}
	if (!_mouseState.rgbButtons[0]) {
		isClick = false;
	}
}

void MinerSelect::Draw()
{
	//DrawTexture(background, _x,_y,0, 2, 2, 0, 1);
	DrawTexture(tMiner, _x-220, _y-114, 0.3, 2, 2, 0, 1);
	DrawTexture(tMiner2, _x - 140, _y - 114, 0.3, 2, 2, 0, 1);
	DrawTexture(tMiner3, _x - 60, _y - 114, 0.3, 2, 2, 0, 1);

//	DrawTexture(tPlus, _x - 220, _y - 40, 0.3, 2, 2, 0, 1);
//	DrawTexture(tPlus, _x - 140, _y - 40, 0.3, 2, 2, 0, 1);
//	DrawTexture(tPlus, _x - 60, _y - 40, 0.3, 2, 2, 0, 1);

	SetSamplerStateNone();
}

void MinerSelect::Destroy()
{

}