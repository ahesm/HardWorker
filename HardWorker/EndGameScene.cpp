#include"EndGameScene.h"

#include"Progress.h"
#include"MineScene.h"
#include"Miner.h"

extern int m_count1;
extern int m_count2;
extern int m_count3;

extern int day;

extern float shake, shakeX, shakeY;


void EndGameScene::Initialize()
{
	background = ResourceManager::GetTexture("mine_back");
	tMinecart_b = ResourceManager::GetTexture("minecart_body");
	tMinecart_w[0] = ResourceManager::GetTexture("minecar_wheel1");
	tMinecart_w[1] = ResourceManager::GetTexture("minecar_wheel2");
	tMiner = ResourceManager::GetTexture("miner");
	tSMiner = ResourceManager::GetTexture("poster_worker");
	tMiner2 = ResourceManager::GetTexture("miner_expert");
	tSMiner2 = ResourceManager::GetTexture("poster_expert");
	tMiner3 = ResourceManager::GetTexture("miner_professional");
	tSMiner3 = ResourceManager::GetTexture("poster_professional");
	tDay = ResourceManager::GetTexture("day");
	numbers = ResourceManager::GetTexture("number_black");

	_x = -_sceneWIDTH / 2;
	_y = _sceneHEIGHT / 2;
	cart_x = _sceneWIDTH + 70;
	cart_y = 157 * 2;
	acc2 = -10;
}

void EndGameScene::Step()
{
	if (!flying){
		auto progress = (Progress*)_parent->GetInstance("progress");
		if (progress->end){
			if (once){
				for (int i = 0; i < m_count1; i++)
				{
					_mine *m = new _mine;
					m->_x = cart_x + Random::rand.NextInt(tMinecart_b->_width * 2 - 48) - tMinecart_b->_width + 24;
					m->_y = cart_y - Random::rand.NextInt(15) - 30;
					m->tag = "m_normal";
					_mines.push_back(m);
				}
				for (int i = 0; i < m_count2; i++)
				{
					_mine *m = new _mine;
					m->_x = cart_x + Random::rand.NextInt(tMinecart_b->_width * 2 - 48) - tMinecart_b->_width + 24;
					m->_y = cart_y - Random::rand.NextInt(15) - 30;
					m->tag = "m_expert";
					_mines.push_back(m);
				}
				for (int i = 0; i < m_count3; i++)
				{
					_mine *m = new _mine;
					m->_x = cart_x + Random::rand.NextInt(tMinecart_b->_width * 2 - 48) - tMinecart_b->_width + 24;
					m->_y = cart_y - Random::rand.NextInt(15) - 30;
					m->tag = "m_master";
					_mines.push_back(m);
				}
				once = false;
			}
			acc += 0.015f;
			if (_x >= _sceneWIDTH / 2){
				out = true;
				//progress->end = false;
				_x = _sceneWIDTH / 2;
				_y = _sceneHEIGHT / 2;
			}

			for (ObjectMap::iterator i = _parent->_instances.begin(); i != _parent->_instances.end(); i++){
				(*i).second->_direction = 0;
				(*i).second->_speed += acc;
				if (out) (*i).second->_speed = 0;
			}
		}
	}
	if (out){
		acc2 += 0.1f;
		angle -= 5;
		if (acc2 >= -1.0f) acc2 = -1.0f;
		cart_x += acc2;
		for (int i = 0; i < _mines.size(); i++) _mines[i]->_x += acc2;
		if (cart_x  < _sceneWIDTH / 2 - 160){
			//ReplaceScene(new MineScene);
			out = false;
			flying = true;
		}

	}
	if (flying){
		if (alpha >= 0) alpha -= 0.038;
		else {
			alpha = 0.0f; 
			_parent->ReplaceScene(new MineScene);
			return;
		}
		for (int i = 0; i < _mines.size(); i++)
		{
			if (gravity <= 8){
				_mines[i]->_y -= gravity;			
			}
		}
		gravity += 0.4;
	}

}

void EndGameScene::Draw()
{
	//DrawTexture(background, _x + _sceneWIDTH/2, _y, 0,2,2, 0, 1);
	DrawTexturePart(background, _x - _sceneWIDTH/2+shakeX, _y - _sceneHEIGHT/2+shakeY, 0.1, 0, 0, 232, 200, 0, 0, 2, 2, 0, 1);
	DrawTexturePart(background, _x + 232 * 2 - _sceneWIDTH/2+shakeX, _y - _sceneHEIGHT/2+shakeY, 0.3, 232, 0, 560 - 232, 200, 0, 0, 2, 2, 0, 1);
	
	for (int i = 0; i < _mines.size(); i++){
		if (_mines[i]->tag == "m_normal")
			DrawTexture(tMiner, _mines[i]->_x, _mines[i]->_y,0.1,-2,2, 0, alpha);
		else if (_mines[i]->tag == "m_expert")
			DrawTexture(tMiner2, _mines[i]->_x, _mines[i]->_y, 0.1, -2, 2, 0, alpha);
		else if (_mines[i]->tag == "m_master")
			DrawTexture(tMiner3, _mines[i]->_x, _mines[i]->_y, 0.1, -2, 2, 0, alpha);
	}

	DrawTexture(tMinecart_w[1], cart_x + 5, cart_y + 20, 0.2, 2, 2, angle, 1);
	DrawTexture(tMinecart_w[1], cart_x - 32, cart_y + 20, 0.2, 2, 2, angle, 1);
	DrawTexture(tMinecart_b, cart_x, cart_y - 5, 0.2, 2, 2, 0, 1);
	DrawTexture(tMinecart_w[0], cart_x + 32, cart_y + 20, 0.2, 2, 2, angle, 1);
	DrawTexture(tMinecart_w[0], cart_x - 5, cart_y + 20, 0.2, 2, 2, angle, 1);
	DrawTexture(tSMiner, _x - 220, _y - 114, 0.5, 2, 2, 0, 1);
	DrawTexture(tSMiner2, _x - 140, _y - 114, 0.5, 2, 2, 0, 1);
	DrawTexture(tSMiner3, _x - 60, _y - 114, 0.5, 2, 2, 0, 1);

	DrawTexture(tDay, _sceneWIDTH - 100, 7.5, 0.7, 0, 0, 2, 2, 0, 1);
	DrawNumber(numbers, day, 6, _sceneWIDTH - 30, 15, 0.9, 2, 2, 1, 0);
}

void EndGameScene::Destroy()
{
}