#ifndef _ANIMATIONMANAGER_H_
#define _ANIMATIONMANAGER_H_

#include "Root.h"
#include "Object.h"
#include "Timer.h"

class AnimationManager : public Root
{
public:
	static AnimationManager *Create(Object *object, Texture *texture, int width, int height, int first, int count, int interval);

	void SetAnimate(int start, int count);

	void Draw(float x, float y, float z, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha);

	bool IsAnimationEnd();

private:
	void DrawPart(float x, float y, float z, int step, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha);

private:
	Texture *_texture;
	Timer *_timer;

	bool _isFirst = true;

	int _width, _height;
	int _interval = 0;
	int _step = 0;
	int _first = 0;
	int _count = 0;

};

#endif