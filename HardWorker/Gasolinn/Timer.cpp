#include "Timer.h"

#include "Scene.h"
#include "Application.h"

Timer *Timer::Create(Scene *parent)
{
	auto timer = new Timer;
	timer->_scene = parent;

	return timer;
}

void Timer::Start(int interval, const std::function<void()> &function)
{
	if (!isFirst) {
		startTick = _scene->_tick;
		isFirst = true;
	}

	if (_scene->_tick - startTick >= interval) {
		startTick = _scene->_tick;

		function();
	}
}