#include"IngameMiner.h"


void IngameMiner::Initialize()
{
	if (_tag == "ingameMiner")
	{
		hp = 120;
		mineral = 0;
		tick = Random::rand.NextInt(20) + 60;
		passion = Random::rand.NextInt(6) + 2;
		advance = Random::rand.NextInt(6) + 6;
		timer = Timer::Create(_parent);
		dead = false;
	}
	if (_tag == "ingameMiner2")
	{
		hp = 200;
		mineral = 0;
		tick = Random::rand.NextInt(10) + 40;
		passion = Random::rand.NextInt(8) + 4;
		advance = Random::rand.NextInt(6) + 10;
		timer = Timer::Create(_parent);
		dead = false;
	}
	if (_tag == "ingameMiner3")
	{
		hp = 500;
		mineral = 0;
		tick = Random::rand.NextInt(10) + 20;
		passion = Random::rand.NextInt(10) + 5;
		advance = Random::rand.NextInt(10) + 20;
		timer = Timer::Create(_parent);
		dead = false;
	}
}

void IngameMiner::Step()
{

}

void IngameMiner::Draw()
{

}

void IngameMiner::Destroy()
{
}