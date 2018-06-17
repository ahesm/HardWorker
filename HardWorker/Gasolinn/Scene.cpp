#include "Scene.h"

#include "Application.h"
#include "IDManager.h"

void Scene::Background(DWORD dt)
{
	_tick = dt;
	_device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(126, 95, 45), 1.0f, 0);
	if (SUCCEEDED(_device->BeginScene()))
	{
		_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);

		TimelineMap::iterator timEnd = _timelines.end();
		for (_timIter = _timelines.begin(); _timIter != timEnd;)
		{
			(*_timIter).second->_Background();
		}

		ObjectMap::iterator objEnd = _instances.end();
		for (_insIter = _instances.begin(); _insIter != objEnd;)
		{
			(*_insIter).second->_Background();
		}

		_sprite->End();
		_device->EndScene();
	}
	_device->Present(NULL, NULL, NULL, NULL);
}

void Scene::Pause()
{
	_isPause = true;
}

void Scene::Resume()
{
	_isPause = false;
}

void Scene::CreateInstanceWithTag(Object *object, float x, float y, float direction, float speed, const std::string &tag)
{
	object->_parent = this;
	object->_id = IDManager::AssignID();
	object->_x = x;
	object->_y = y;
	object->_direction = direction;
	object->_speed = speed;
	object->_tag = tag;
	object->Initialize();
	_instances.insert(std::make_pair(object->_id, object));
}

void Scene::CreateInstanceWithTag(Object *object, float x, float y, const std::string &tag)
{
	CreateInstanceWithTag(object, x, y, 0, 0, tag);
}

void Scene::CreateInstanceWithTag(Object *object, const std::string &tag)
{
	CreateInstanceWithTag(object, 0, 0, 0, 0, tag);
}

void Scene::CreateInstance(Object *object, float x, float y, float direction, float speed)
{
	CreateInstanceWithTag(object, x, y, direction, speed, "-980122");
}

void Scene::CreateInstance(Object *object, float x, float y)
{
	CreateInstance(object, x, y, 0, 0);
}

void Scene::CreateInstance(Object *object)
{
	CreateInstance(object, 0, 0);
}

Object *Scene::GetInstance(int id)
{
	return _instances.find(id)->second;
}

Object *Scene::GetInstance(const std::string &tag)
{
	ObjectMap::iterator end =  _instances.end();
	for (ObjectMap::iterator iterator = _instances.begin(); iterator != end; iterator++) {
		if (iterator->second->_tag == tag) {
			return iterator->second;
		}
	}

	return nullptr;
}

void Scene::CreateTimeline(Timeline *timeline)
{
	timeline->_parent = this;
	_timelines.insert(std::make_pair(IDManager::AssignTimelineID(), timeline));
}

void Scene::ReplaceScene(Scene *scene)
{
	scene->_super = this->_super;
	_super->_scenes[PREVIOUS] = this;
	scene->Initialize();
	_super->_scenes[CURRENT] = scene;
}

void Scene::ReplaceSceneWithData(Scene *scene, ExtraData *data)
{
	scene->_data = data;
	ReplaceScene(scene);
}