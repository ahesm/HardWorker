#include "Label.h"

#include "Function.h"

Label *Label::Create(ID3DXFont *font, float x, float y)
{
	Label *label = new Label;
	label->_font = font;
	label->_x = x;
	label->_y = y;
	label->_color = D3DXCOLOR(0, 0, 0, 1);

	return label;
}

const Size &Label::CalcText(ID3DXFont *font, const std::wstring &Label)
{
	Size size;
	RECT rc;
	font->DrawTextW(_sprite, Label.c_str(), -1, &rc, DT_CALCRECT, 0x00000000);
	size.width = rc.right - rc.left;
	size.height = rc.bottom - rc.top;

	return size;
}

void Label::SetText(const std::wstring &text)
{
	if (!_isFirst)
		_texture->Release();

	this->_text = text;

	RECT rc;
	_font->DrawTextW(_sprite, text.c_str(), -1, &rc, DT_CALCRECT, 0x00000000);
	_width = rc.right - rc.left;
	_height = rc.bottom - rc.top;

	IDirect3DSurface9 *targetSurface;
	IDirect3DSurface9 *backbuffer;

	D3DXCreateTexture(_device, _width, _height, 0, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_texture);/// 렌더타겟 텍스쳐 생성

	_texture->GetSurfaceLevel(0, &targetSurface);/// 텍스쳐의 서피스를 targetSurface에 넣기
	_device->GetRenderTarget(0, &backbuffer);/// 현재 렌더타겟 가져오기

	_device->SetRenderTarget(0, targetSurface);/// 렌더타겟을 targetSurface로 하기

	_device->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	ID3DXSprite *sprite;
	D3DXCreateSprite(_device, &sprite);

	_device->BeginScene();
	sprite->Begin(0);

	RECT rt = { 0, 0, _width, _height };
	_font->DrawTextW(sprite, text.c_str(), -1, &rt, 0, D3DXCOLOR(1, 1, 1, 1));/// 폰트 그리기

	sprite->End();
	_device->EndScene();

	_device->SetRenderTarget(0, backbuffer);/// 렌더타겟 원래대로 돌리기

	//	D3DXSaveSurfaceToFileA("surface.png", D3DXIFF_PNG, targetSurface, 0, 0);
	//	D3DXSaveLabelureToFileA("texture.png", D3DXIFF_PNG, _texture, 0);

	backbuffer->Release();
	targetSurface->Release();
	sprite->Release();
	_isFirst = false;
}

void Label::SetColor(const D3DXCOLOR &color)
{
	this->_color = color;
}

void Label::SetColor(int r, int g, int b)
{
	SetColor(D3DCOLOR_XRGB(r, g, b));
}

void Label::SetShadow(float angle, const D3DXCOLOR &color)
{
	_isShadow = true;
	_shadowAngle = angle;
	_shadowColor = color;
}

void Label::Draw()
{
	if (_isShadow)
		DrawText(_x + Fn::Cos(_shadowAngle), _y - Fn::Sin(_shadowAngle), _z, _centerX, _centerY, _angle, _alpha, _shadowColor);
	DrawText(_x, _y, _z, _centerX, _centerY, _angle, _alpha, _color);
}

void Label::DrawText(float x, float y, float z, float centerX, float centerY, float angle, float alpha, const D3DXCOLOR &color)
{
	RECT rc = { 0, 0, _width, _height };

	D3DXMATRIX matrix;

	D3DXQUATERNION q;

	D3DXQuaternionRotationAxis(&q, &D3DXVECTOR3(0, 0, 1), D3DXToRadian(angle));
	D3DXMatrixTransformation(&matrix, NULL, NULL, &D3DXVECTOR3(1, 1, 0), NULL, &q, &D3DXVECTOR3(x, y, z));

	_sprite->SetTransform(&matrix);
	_sprite->Draw(_texture, &rc, &D3DXVECTOR3(_width*centerX, _height*centerY, 0), NULL, D3DXCOLOR(color.r, color.g, color.b, alpha));
}

void Label::Release()
{
	_texture->Release();
	delete this;
}