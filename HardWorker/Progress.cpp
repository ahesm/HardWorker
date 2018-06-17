#include"Progress.h"

#include"IngameMiner.h"
#include "FadeOut.h"

extern int money;
extern int amount;
extern bool changed;

extern float shake, shakeX, shakeY;
	

int maejang = 1000;
int chuk = 0;
bool win = false;
bool failed = false;

int m_count1 = 0;
int m_count2 = 0;
int m_count3 = 0;

void Progress::Initialize()
{
	m_count1 = 0;
	m_count2 = 0;
	m_count3 = 0;
	_x = _sceneWIDTH / 2;
	_y = _sceneHEIGHT / 2 - 170;
	prog_bar = ResourceManager::GetTexture("progress");
	prog_outline = ResourceManager::GetTexture("progress_outline");
	prog_scale = ResourceManager::GetTexture("progress_cursor");
	btn_return = ResourceManager::GetTexture("stop");
	tamount = ResourceManager::GetTexture("amount");
	tmoney = ResourceManager::GetTexture("money");
	numbers = ResourceManager::GetTexture("number_black");
	for (int i = 0; i < *(int*)_parent->_data->GetData("count_miner");i++){
		IngameMiner *im = new IngameMiner;
		miners.push_back(im);
		_parent->CreateInstanceWithTag(im,"ingameMiner");
		m_count1++;
	}for (int i = 0; i < *(int*)_parent->_data->GetData("count_miner2"); i++){
		IngameMiner *im = new IngameMiner;
		_parent->CreateInstanceWithTag(im,"ingameMiner2");
		miners.push_back(im);
		m_count2++;
	}for (int i = 0; i < *(int*)_parent->_data->GetData("count_miner3"); i++){
		IngameMiner *im = new IngameMiner;
		_parent->CreateInstanceWithTag(im, "ingameMiner3");
		miners.push_back(im);
		m_count3++;
	}
	none_dead = miners.size();
	prog_degree = 0.0f;
	prog_degree_ = 0.0f;
	return_on = false;
	end = false;
	_tag = "progress";
	scale_x = _x - prog_bar->_width + 4;
}

void Progress::Step()
{
	if (Input::MouseUp(MOUSE_LEFT))
	{
		if (Fn::CollisionWithMouse(_mouse, _x + 220, _y + 70, btn_return->_width *2, btn_return->_height *2))
		{
			amount = 0;
			for (int i = 0; i < miners.size(); i++){				
				if (miners[i]->hp <= 0)
					amount += miners[i]->mineral / 2;
				else
					amount += miners[i]->mineral;
			}
			changed = true;
			return_on = true;
		}
	}

	if (!return_on&&prog_degree >= maejang){
		return_on = true;
		win = true;
	}

	if (!end){
		if (return_on){
			prog_degree -= 5;
			if (!win_once){ 
				win_once = true;
			}
			if (prog_degree <= 0){
				prog_degree = 0;
				if (win) maejang = 1000 + 500 * ++chuk;
				if (!win) maejang -= prog_degree_;
				prog_degree_ = 0;
				end = true;
			}
		}
		else{
			if (!end)
				scale_x += (_x - prog_bar->_width + 4 + prog_degree / maejang * prog_bar->_width * 2 - scale_x) / 10;
			for (int i = 0; i < miners.size(); i++){
				miners[i]->timer->Start(miners[i]->tick, [&](){
					miners[i]->hp -= miners[i]->passion;
					SoundEngine::GetInstance().PlaySE("sfx2", false);
					shake = 5;
					if (miners[i]->_tag == "ingameMiner")
						miners[i]->tick = Random::rand.NextInt(20) + 60;
					if (miners[i]->_tag == "ingameMiner2")
						miners[i]->tick = Random::rand.NextInt(10) + 40;
					if (miners[i]->_tag == "ingameMiner3")
						miners[i]->tick = Random::rand.NextInt(5) + 20;
					if (miners[i]->hp <= 0){
						if (!miners[i]->dead){
							prog_degree_ -= miners[i]->mineral / 2;
							_parent->CreateInstanceWithTag(new SmallThing, _x - prog_bar->_width + 4 + prog_degree / maejang * prog_bar->_width * 2, _y, "rip");
							miners[i]->dead = true;
							none_dead--;
							if (miners[i]->_tag == "ingameMiner") m_count1--;
							if (miners[i]->_tag == "ingameMiner2") m_count2--;
							if (miners[i]->_tag == "ingameMiner3") m_count3--;
						}
						if (none_dead == 0){
							failed = true;
							return_on = true;
						}
					}
					else {
						miners[i]->mineral += miners[i]->advance;
						prog_degree += miners[i]->advance;
						prog_degree_ += miners[i]->advance;
					}
				});
			}
		}
	}
}

void Progress::Draw()
{
	DrawTexture(prog_bar, _x/*+shakeX*/, _y/* +shakeY*/+ 20, 0.5, 2, 2, 0, 1);
	if (!return_on){
		DrawTexture(prog_scale, scale_x, _y + 20 + 20, 0.5, 2, 2, 0, 1);
	}
	else{
		DrawTexture(prog_scale, _x - prog_bar->_width + 4 + prog_degree / maejang * prog_bar->_width * 2, _y + 20 + 20, 0.5, 2, 2, 0, 1);
	}
	DrawTexture(btn_return, _x + 220, _y + 65, 0.5, 2,2, 0, 1);
	DrawTexture(tamount, _x - 270, _y + 70, 0.5,0,0, 2, 2, 0, 1);
	DrawTexture(tmoney, _x - 270, _y + 105, 0.5,0,0, 2, 2, 0, 1);
	DrawNumber(numbers, none_dead, 6, _x - 155, _y + 77, 0.5, 2, 2, 1, 0);
	DrawNumber(numbers, prog_degree_, 6, _x - 170, _y + 112, 0.5, 2, 2, 1, 0);
}

void Progress::Destroy()
{

}