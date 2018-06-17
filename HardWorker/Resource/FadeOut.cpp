#include"FadeOut.h"

float shake = 0, shakeX = 0, shakeY = 0;


void FadeOut::Initialize()
{
	tBlack = ResourceManager::GetTexture("black");
	alpha = 1.0f;
}

void FadeOut::Step()
{
	if (alpha > 0.0f) {
		alpha -= 0.02f;
	}
	else alpha = 0.0f;

	if (shake != 0) {
		shake -= shake / 20;
		shakeX = Random::rand.NextInt(shake * 2) - shake;
		shakeY = Random::rand.NextInt(shake * 2) - shake;
	}

	printf("%f\n", shake);
}

void FadeOut::Draw()
{
	DrawTexture(tBlack, _sceneWIDTH / 2, _sceneHEIGHT / 2, 1, 0, alpha);
}

void FadeOut::Destroy()
{

}