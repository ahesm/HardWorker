#ifndef _TIMER_H_
#define _TIMER_H_

#include <Windows.h>
#include <functional>

class Scene;

class Timer
{
private:
	DWORD startTick;
	bool isFirst = false;
	Scene *_scene;

public:
	static Timer *Create(Scene *parent);
	void Start(int interval, const std::function<void()> &function);
	/// 1ms

};

#endif