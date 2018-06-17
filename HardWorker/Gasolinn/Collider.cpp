#include "Collider.h"

#include "Object.h"
#include "Scene.h"

Collider *Collider::CreateRectangle(Object *parent, float x, float y, int width, int height)
{
	auto collider = new Collider;

	collider->_parent = parent;
	collider->_type = RECTANGLE;
	collider->_x = x;
	collider->_y = y;
	collider->_width = width;
	collider->_height = height;

	return collider;
}

Collider *Collider::CreateCircle(Object *parent, float x, float y, int diameter)
{
	auto collider = new Collider;

	collider->_parent = parent;
	collider->_type = CIRCLE;
	collider->_x = x;
	collider->_y = y;
	collider->_diameter = diameter;

	return collider;
}


void Collider::IsCollision(const std::function<void(int id)> &function)
{
	ColliderMap::iterator iterator;
	ColliderMap::iterator end = _parent->_parent->_colliders.end();
	for (iterator = _parent->_parent->_colliders.begin(); iterator != end;)
	{
		if ((*iterator).second == this || !(*iterator).second->_enable) {
			if ((*iterator).second->_isDestroy)
				_parent->_parent->_colliders.erase(iterator++);
			else
				iterator++;

			continue;
		}

		if ((*iterator).second->_type == RECTANGLE) {
			if (_CollisionToRectangle((*iterator).second)) {
				function((*iterator).second->_id);
			}
		}
		else if ((*iterator).second->_type == CIRCLE) {
			if (_CollisionToCircle((*iterator).second)) {
				function((*iterator).second->_id);
			}
		}
		
		if ((*iterator).second->_isDestroy)
			_parent->_parent->_colliders.erase(iterator++);
		else
			iterator++;

	}
}

void Collider::IsCollisionWithTag(const std::string &tag, const std::function<void(int id)> &function)
{
	ColliderMap::iterator iterator;
	ColliderMap::iterator end = _parent->_parent->_colliders.end();
	for (iterator = _parent->_parent->_colliders.begin(); iterator != end;)
	{
		if ((*iterator).second == this || !(*iterator).second->_enable || (*iterator).second->_parent->_tag != tag) {
			if ((*iterator).second->_isDestroy)
				_parent->_parent->_colliders.erase(iterator++);
			else
				iterator++;

			continue;
		}

		if ((*iterator).second->_type == RECTANGLE) {
			if (_CollisionToRectangle((*iterator).second)) {
				function((*iterator).second->_id);
			}
		}
		else if ((*iterator).second->_type == CIRCLE) {
			if (_CollisionToCircle((*iterator).second)) {
				function((*iterator).second->_id);
			}
		}

		if ((*iterator).second->_isDestroy)
			_parent->_parent->_colliders.erase(iterator++);
		else
			iterator++;

	}
}

void Collider::SetLocation(float x, float y)
{
	this->_x = x;
	this->_y = y;
}

void Collider::Destroy()
{
	_isDestroy = true;
}

bool Collider::_CollisionToRectangle(Collider *other)
{
	if (_type == RECTANGLE) {
		if (this->_x + this->_width / 2 >= other->_x - other->_width / 2 && this->_x - this->_width / 2 <= other->_x + other->_width / 2
			&& this->_y + this->_height / 2 >= other->_y - other->_height / 2 && this->_y - this->_height / 2 <= other->_y + other->_height / 2)
		{
			return true;
		}
		return false;
	}
	else if (_type == CIRCLE) {
		float left_x = other->_x - other->_width / 2;
		float right_x = other->_x + other->_width / 2;
		float up_y = other->_y - other->_height / 2;
		float down_y = other->_y + other->_height / 2;

		if ((left_x <= this->_x && right_x >= this->_x) || (up_y <= this->_y && down_y >= this->_y))
		{
			if ((this->_x - this->_diameter / 2 <= right_x) && (this->_x + this->_diameter / 2 >= left_x) && (this->_y - this->_diameter / 2 <= down_y) && (this->_y + this->_diameter / 2 >= up_y))
				return true;
		}
		else
		{
			float len = abs(left_x - this->_x)*abs(left_x - this->_x) + abs(up_y - this->_y)*abs(up_y - this->_y);//좌상단과 원 중심점
			if (len <= (this->_diameter / 2)*(this->_diameter / 2)) return true;
			len = abs(left_x - this->_x)*abs(left_x - this->_x) + abs(down_y - this->_y)*abs(down_y - this->_y);//좌하단과 원 중심점
			if (len <= (this->_diameter / 2)*(this->_diameter / 2)) return true;
			len = abs(right_x - this->_x)*abs(right_x - this->_x) + abs(up_y - this->_y)*abs(up_y - this->_y);//우상단과 원 중심점
			if (len <= (this->_diameter / 2)*(this->_diameter / 2)) return true;
			len = abs(right_x - this->_x)*abs(right_x - this->_x) + abs(down_y - this->_y)*abs(down_y - this->_y);//우하단과 원 중심점
			if (len <= (this->_diameter / 2)*(this->_diameter / 2)) return true;
		}

		return false;
	}
}

bool Collider::_CollisionToCircle(Collider *other)
{
	if (_type == RECTANGLE) {
		float left_x = this->_x - this->_width / 2;
		float right_x = this->_x + this->_width / 2;
		float up_y = this->_y - this->_height / 2;
		float down_y = this->_y + this->_height / 2;

		if ((left_x <= other->_x && right_x >= other->_x) || (up_y <= other->_y && down_y >= other->_y))
		{
			if ((other->_x - other->_diameter / 2 <= right_x) && (other->_x + other->_diameter / 2 >= left_x) && (other->_y - other->_diameter / 2 <= down_y) && (other->_y + other->_diameter / 2 >= up_y))
				return true;
		}
		else
		{
			float len = abs(left_x - other->_x)*abs(left_x - other->_x) + abs(up_y - other->_y)*abs(up_y - other->_y);//좌상단과 원 중심점
			if (len <= (other->_diameter / 2)*(other->_diameter / 2)) return true;
			len = abs(left_x - other->_x)*abs(left_x - other->_x) + abs(down_y - other->_y)*abs(down_y - other->_y);//좌하단과 원 중심점
			if (len <= (other->_diameter / 2)*(other->_diameter / 2)) return true;
			len = abs(right_x - other->_x)*abs(right_x - other->_x) + abs(up_y - other->_y)*abs(up_y - other->_y);//우상단과 원 중심점
			if (len <= (other->_diameter / 2)*(other->_diameter / 2)) return true;
			len = abs(right_x - other->_x)*abs(right_x - other->_x) + abs(down_y - other->_y)*abs(down_y - other->_y);//우하단과 원 중심점
			if (len <= (other->_diameter / 2)*(other->_diameter / 2)) return true;
		}

		return false;
	}
	else if (_type == CIRCLE) {
		float len = abs(this->_x - other->_x)*abs(this->_x - other->_x) + abs(this->_y - other->_y)*abs(this->_y - other->_y);

		if ((this->_diameter / 2 + other->_diameter / 2)*(this->_diameter / 2 + other->_diameter / 2) >= len) {
			return true;
		}
		return false;
	}
}