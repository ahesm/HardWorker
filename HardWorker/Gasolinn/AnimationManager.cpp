#include "AnimationManager.h"

AnimationManager *AnimationManager::Create(Object *object, Texture *texture, int width, int height, int first, int count, int interval)
{
	auto am = new AnimationManager;
	am->_timer = Timer::Create(object->_parent);
	am->_texture = texture;

	am->_width = width;
	am->_height = height;
	am->_first = first;
	am->_count = count;
	am->_interval = interval;

	return am;
}

void AnimationManager::SetAnimate(int start, int count)
{
	this->_first = start;
	this->_count = count;
}

bool AnimationManager::IsAnimationEnd()
{
	if (!_isFirst) {
		if (_step == 0)
			return true;
	}
	return false;
}

void AnimationManager::Draw(float x, float y, float z, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha)
{
	DrawPart(x, y, z, _step, centerX, centerY, scaleX, scaleY, angle, alpha);

	_timer->Start(_interval, [&]{
		_step += 1;
		_isFirst = false;
		if (_step >= _count + _first)
		{
			_step = _first;
		}
	});
}

void AnimationManager::DrawPart(float x, float y, float z, int step, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha)
{
	int xcount = _texture->_width / _width;
	int ycount = step / xcount;

	step %= xcount;

	RECT rc = { step*_width, ycount*_height, step*_width + _width, ycount*_height + _height };

	D3DXMATRIX matrix;

	D3DXQUATERNION q;

	D3DXQuaternionRotationAxis(&q, &D3DXVECTOR3(0, 0, 1), D3DXToRadian(angle));
	D3DXMatrixTransformation(&matrix, NULL, NULL, &D3DXVECTOR3(scaleX, scaleY, 0), NULL, &q, &D3DXVECTOR3(x, y, z));

	_sprite->SetTransform(&matrix);
	_sprite->Draw(_texture->_texture, &rc, &D3DXVECTOR3(_width * centerX, _height * centerY, 0), NULL, D3DXCOLOR(1, 1, 1, alpha));
}