#include "Object.h"

#include "ResourceManager.h"
#include "Scene.h"
#include "Function.h"
#include "IDManager.h"

void Object::_Background()
{

	/* 심각한 문제 하나.!
	 * pause상태에서 resume 상태가 되려면 draw에서 Resume()을 호출해야 하지만 autodraw를 끄면 draw가 항상 호출되지 않아버린다...
	 */
	_previousX = _x;
	_previousY = _y;

	if (_parent->_isAutoDraw)
		Draw();

	if (_speed != 0) {
		_x += Fn::LengthDirX(_speed, _direction);
		_y += Fn::LengthDirY(_speed, _direction);
	}

	if (!_parent->_isPause)
		Step();

	if (_isDestroy) {
		_parent->_instances.erase(_parent->_insIter++);
		return;
	}
	else {
		++_parent->_insIter;
	}
}

void Object::SetSamplerStateNone()
{
	_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
	_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
	_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
}

void Object::ReDraw()
{
	ObjectMap::iterator iter;
	ObjectMap::iterator end = _parent->_instances.end();
	for (iter = _parent->_instances.begin(); iter != end; iter++) {
		if ((*iter).first == (_id))
			continue;
		else
			(*iter).second->Draw();
	}
}

void Object::SetRenderTarget(IDirect3DSurface9 *surface)
{
	_device->GetRenderTarget(0, &_parent->_backbuffer);
	_device->SetRenderTarget(0, surface);

	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);
}

void Object::ResetRenderTarget()
{
	_sprite->End();
	_device->SetRenderTarget(0, _parent->_backbuffer);
}

void Object::BeginShader(ID3DXEffect *shader)
{
	_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);

	shader->Begin(0, 0);
	shader->BeginPass(0);
}

void Object::EndShader(ID3DXEffect *shader)
{
	_sprite->End();

	shader->CommitChanges();
	shader->EndPass();
	shader->End();
}

Texture *Object::CreateTexture(int width, int height)
{
	auto *texture = new Texture;
	D3DXCreateTexture(_device, width, height, 0, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture->_texture);
	texture->_width = width;
	texture->_height = height;

	return texture;
}

void Object::ReplaceScene(Scene *scene)
{
	_parent->ReplaceScene(scene);
}

void Object::ReplaceSceneWithData(Scene *scene, ExtraData *data)
{
	_parent->ReplaceSceneWithData(scene, data);
}

void Object::DrawTexturePart(Texture *texture, float x, float y, float z, int left, int top, int width, int height, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha, const D3DXCOLOR &color)
{
	RECT rc = { left, top, left + width, top + height };

	D3DXMATRIX matrix;

	D3DXQUATERNION quaternion;

	D3DXQuaternionRotationAxis(&quaternion, &D3DXVECTOR3(0, 0, 1), D3DXToRadian(angle));
	D3DXMatrixTransformation(&matrix, NULL, NULL, &D3DXVECTOR3(scaleX, scaleY, 0), NULL, &quaternion, &D3DXVECTOR3(x, y, z));

	_color = color;
	_color.a = alpha;

	_sprite->SetTransform(&matrix);
	_sprite->Draw(texture->_texture, &rc, &D3DXVECTOR3(width * centerX, height * centerY, 0), NULL, _color);
}

void Object::DrawTexturePart(Texture *texture, float x, float y, float z, int left, int top, int width, int height, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha)
{
	DrawTexturePart(texture, x, y, z, left, top, width, height, centerX, centerY, scaleX, scaleY, angle, alpha, _color);
}

void Object::DrawTexture(Texture *texture, float x, float y, float z, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha, const D3DXCOLOR &color)
{
	/*
	RECT rc = { 0, 0, texture->_width, texture->_height };

	D3DXMATRIX matrix;

	D3DXQUATERNION quaternion;

	D3DXQuaternionRotationAxis(&quaternion, &D3DXVECTOR3(0, 0, 1), D3DXToRadian(angle));
	D3DXMatrixTransformation(&matrix, NULL, NULL, &D3DXVECTOR3(scaleX, scaleY, 0), NULL, &quaternion, &D3DXVECTOR3(x, y, z));

	_color = color;
	_color.a = alpha;

	_sprite->SetTransform(&matrix);
	_sprite->Draw(texture->_texture, &rc, &D3DXVECTOR3(texture->_width * centerX, texture->_height * centerY, 0), NULL, _color);
	*/
	DrawTexturePart(texture, x, y, z, 0, 0, texture->_width, texture->_height, centerX, centerY, scaleX, scaleY, angle, alpha, color);
}

void Object::DrawTexture(Texture *texture, float x, float y, float z, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha)
{
	_color.a = alpha;
	DrawTexture(texture, x, y, z, centerX, centerY, scaleX, scaleY, angle, alpha, _color);
}

void Object::DrawTexture(Texture *texture, float x, float y, float z, float scaleX, float scaleY, float angle, float alpha)
{
	DrawTexture(texture, x, y, z, _centerX, _centerY, scaleX, scaleY, angle, alpha);
}

void Object::DrawTexture(Texture *texture, float x, float y, float z, float angle, float alpha)
{
	DrawTexture(texture, x, y, z, _scaleX, _scaleY, angle, alpha);
}

void Object::DrawSelf(Texture *texture)
{
	DrawTexture(texture, _x, _y, _z, _angle, _alpha);
}


int Object::DrawNumber(Texture *texture, int number, int space, float x, float y, float z, float scaleX, float scaleY, float alpha, int align)
{
	int numlen = strlen(std::to_string(number).data());

	int w = texture->_width / 10;
	int h = texture->_height;

	double skv_m = w + space;//(space*(numlen - 1)) - (space*(numlen / 2));

	int skv_k = 1;

	for (int i = numlen - 1; i >= 0; i--){
		int div = floor(number / skv_k);
		div %= 10;
		int a;
		switch (align) {
		case 0: a = i*skv_m - 1; break;
		case 1: a = i*skv_m - ((numlen) / 2)*skv_m + (1 - numlen % 2)*skv_m / 2 - 1; break;
		case 2: a = i*skv_m - (numlen - 1)*skv_m - 1; break;
		}

		DrawTexturePart(texture, x + a, y, z, div*w, 0, w, h, 0.5, 0.5, scaleX, scaleY, 0, alpha, _color);
		skv_k *= 10;
	}
		return numlen;
}

void Object::DestroyInstance()
{
	Destroy();
	_isDestroy = true;
}

void Object::AddCollider(Collider *collider)
{
	collider->_id = IDManager::AssignColliderID();
	_parent->_colliders.insert(std::make_pair(collider->_id, collider));
}

Collider *Object::GetCollider(int id)
{
	return _parent->_colliders.find(id)->second;
}