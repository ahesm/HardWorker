#ifndef _SCENE_H_
#define _SCENE_H_

#include "Root.h"
#include "Object.h"
#include "Timeline.h"
#include "ExtraData.h"
#include "Collider.h"

class Application;

class Scene : public Root
{
public:
	ObjectMap _instances;
	ObjectMap::iterator _insIter;

	ColliderMap _colliders;
	TimelineMap _timelines;
	TimelineMap::iterator _timIter;

	Application *_super;

	ExtraData *_data;

	IDirect3DSurface9 *_backbuffer;

	DWORD _tick = 0;

	bool _isPause = false;
	bool _isAutoDraw = true;

public:
	virtual void Initialize() = 0;
	virtual void Release() = 0;

	void Background(DWORD dt);

	void Pause();
	void Resume();

public:
	void CreateInstance(Object *object, float x, float y, float direction, float speed);

	void CreateInstance(Object *object, float x, float y);
	void CreateInstance(Object *object);

	void CreateInstanceWithTag(Object *object, float x, float y, float direction, float speed, const std::string &tag);
	void CreateInstanceWithTag(Object *object, float x, float y, const std::string &tag);
	void CreateInstanceWithTag(Object *object, const std::string &tag);

	Object *GetInstance(int id);
	Object *GetInstance(const std::string &tag);

public:
	void CreateTimeline(Timeline *timeline);

public:
	void ReplaceScene(Scene *scene);
	void ReplaceSceneWithData(Scene *scene, ExtraData *data);
};

#endif