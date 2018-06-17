#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include <map>
#include <string>
#include <functional>

class Object;

enum ColliderType{
	RECTANGLE, CIRCLE
};

class Collider
{
public:
	Object *_parent;

	float _x, _y;
	int _width, _height;
	int _diameter;

	int _id;

	bool _enable = true;
	bool _isDestroy = false;

	ColliderType _type;

public:
	static Collider *CreateRectangle(Object *parent, float x, float y, int width, int height);
	static Collider *CreateCircle(Object *parent, float x, float y, int diameter);

	/*매개변수 id는 충돌한 상대 collider의 id*/
	void IsCollision(const std::function<void(int id)> &function);
	void IsCollisionWithTag(const std::string &tag, const std::function<void(int id)> &function);

	void SetLocation(float x, float y);

	void Destroy();

public:
	bool _CollisionToRectangle(Collider *other);
	bool _CollisionToCircle(Collider *other);


};

typedef std::map<int, Collider *> ColliderMap;

#endif