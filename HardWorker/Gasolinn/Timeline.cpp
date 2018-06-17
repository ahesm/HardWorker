#include "Timeline.h"

#include "Scene.h"

void Timeline::_Background()
{
	Step();

	_tick += 1;

	if (_isDestroy) {
		_parent->_timelines.erase(_parent->_timIter++);
		return;
	}
	else
		++_parent->_timIter;
}

void Timeline::End()
{
	_isDestroy = true;
}
