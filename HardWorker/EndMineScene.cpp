#include"EndMineScene.h"

#include"Minecart.h"
#include"GameScene.h"

void EndMineScene::Initialize()
{
	auto minecart = (Minecart*)_parent->GetInstance("minecart");
	data = new ExtraData;
	_x = _sceneWIDTH *3/2;
	_y = _sceneHEIGHT / 2 - 170;
	_tag = "end";
}

void EndMineScene::Step()
{
	if (!ss){
		auto minecart = (Minecart*)_parent->GetInstance("minecart");
		if (minecart->_x >= _sceneWIDTH + 1500){
			on = true;
			minecart->_speed = 0;
			minecart->isStart = false;
			data->PutData(minecart->count_miner, "count_miner");
			data->PutData(minecart->count_miner2, "count_miner2");
			data->PutData(minecart->count_miner3, "count_miner3");
			_parent->CreateInstanceWithTag(new FadeIn, "toGameScene");
		}
		if (on&&!ss){
			acc += 0.015;
			//black_alpha += 0.05f;
			for (ObjectMap::iterator i = _parent->_instances.begin(); i != _parent->_instances.end(); i++)
			{
				if (_x < _sceneWIDTH * 1 / 2){
					for (ObjectMap::iterator i = _parent->_instances.begin(); i != _parent->_instances.end(); i++)
					{
						(*i).second->_speed = 0;
						(*i).second->_x += 10;
					}
					ss = true;
				}
				if ((*i).second != minecart)  {
					(*i).second->_direction = 180;
					(*i).second->_speed += acc;
				}
			}
		}
	}
}

void EndMineScene::Draw()
{
}

void EndMineScene::Destroy()
{

}