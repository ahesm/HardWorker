#ifndef _IDMANAGER_H_
#define _IDMANAGER_H_

#include <map>
#include <string>

class IDManager
{
public:
	static int _id;
	static int _colliderId;
	static int _timelineId;

public:
	static int AssignID();
	static int AssignColliderID();
	static int AssignTimelineID();
};

#endif