#include "IDManager.h"

int IDManager::_id = 0;
int IDManager::_colliderId = 0;
int IDManager::_timelineId = 0;

int IDManager::AssignID()
{
	return _id++;
}

int IDManager::AssignColliderID()
{
	return _colliderId++;
}

int IDManager::AssignTimelineID()
{
	return _timelineId++;
}