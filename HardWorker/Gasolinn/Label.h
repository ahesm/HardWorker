#ifndef _LABEL_H_
#define _LABEL_H_

#include "Root.h"
#include "ResourceManager.h"

#undef DrawText

typedef struct Size{
	int width, height;
}Size;

class Label : public Root
{
public:
	ID3DXFont *_font;
	std::wstring _text;
	LPDIRECT3DTEXTURE9 _texture;

	bool _isFirst = true;

	float _x = 0, _y = 0, _z = 0;
	float _centerX = 0.5, _centerY = 0.5;
	float _alpha = 1;
	float _angle = 0;
	int _width, _height;

	bool _isShadow = false;
	float _shadowAngle = 0;

	D3DXCOLOR _color;
	D3DXCOLOR _shadowColor;

public:
	static Label *Create(ID3DXFont *font, float x, float y);

	static const Size &CalcText(ID3DXFont *font, const std::wstring &text);

	void SetText(const std::wstring &text);

	void SetColor(int r, int g, int b);
	void SetColor(const D3DXCOLOR &color);

	void SetShadow(float angle, const D3DXCOLOR &color);

	void Draw();
	void Release();

private:
	void DrawText(float x, float y, float z, float centerX, float centerY, float angle, float alpha, const D3DXCOLOR &color);
};

#endif
