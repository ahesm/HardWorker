#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Root.h"
#include "Collider.h"

class Scene;
class ExtraData;

class Object : public Root
{
public:
	float _x = 0.0f, _y = 0.0f, _z = 0.0f;
	float _previousX = 0, _previousY = 0;
	float _centerX = 0.5f, _centerY = 0.5f;
	float _scaleX = 1.0f, _scaleY = 1.0f;
	float _angle = 0.0f;
	float _alpha = 1.0f;

	float _speedV = 0.0f, _speedH = 0.0f;/// 세로스피드, 가로스피드
	float _speed = 0.0f;
	float _direction = 0.0f;

	D3DXCOLOR _color = D3DXCOLOR(1, 1, 1, 1);

	bool _isDestroy = false;

	std::string _tag = "-980122";
	int _id;

	Scene *_parent;

public:
	virtual void Initialize() = 0;
	virtual void Step() = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

public:
	void _Background();
	void DestroyInstance();

	void SetSamplerStateNone();

	void ReDraw();

	void SetRenderTarget(IDirect3DSurface9 *surface);
	void ResetRenderTarget();

	void BeginShader(ID3DXEffect *shader);
	void EndShader(ID3DXEffect *shader);

	Texture *CreateTexture(int width, int height);

public:
	void ReplaceScene(Scene *scene);
	void ReplaceSceneWithData(Scene *scene, ExtraData *data);

public:
	void DrawTexturePart(Texture *texture, float x, float y, float z, int left, int top, int width, int height, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha, const D3DXCOLOR &color);
	void DrawTexturePart(Texture *texture, float x, float y, float z, int left, int top, int width, int height, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha);

	void DrawTexture(Texture *texture, float x, float y, float z, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha, const D3DXCOLOR &color);
	void DrawTexture(Texture *texture, float x, float y, float z, float centerX, float centerY, float scaleX, float scaleY, float angle, float alpha);
	void DrawTexture(Texture *texture, float x, float y, float z, float scaleX, float scaleY, float angle, float alpha);
	void DrawTexture(Texture *texture, float x, float y, float z, float angle, float alpha);

	void DrawSelf(Texture *texture);

	int DrawNumber(Texture *texture, int number, int space, float x, float y, float z, float scaleX, float scaleY, float alpha, int align);

public:
	void AddCollider(Collider *collider);
	Collider *GetCollider(int id);

};

typedef std::map<int, Object *> ObjectMap;

#endif