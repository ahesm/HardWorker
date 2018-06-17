#ifndef _TIMELINE_H_
#define _TIMELINE_H_

#include "Root.h"

class Scene;

class Timeline : public Root
{
public:
	Scene *_parent;
	int _tick;
	int _id;

	bool _isDestroy = false;

public:
	virtual void Step() = 0;

public:
	void _Background();
	void End();

};

typedef std::map<int, Timeline *> TimelineMap;

#endif