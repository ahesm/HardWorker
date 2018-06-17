#include "ResourceManager.h"

#include <fstream>
#include <string>

TextureMap ResourceManager::_textures;
ShaderMap ResourceManager::_shaders;
FontMap ResourceManager::_fonts;
SEMap ResourceManager::_ses;
BGMMap ResourceManager::_bgms;

HRESULT ResourceManager::LoadTextureMap(char *path)
{
	std::ifstream in;

	in.open(path, std::ios::in);
	if (!in.is_open())
		return E_FAIL;

	std::string tmp;
	int count = 0;
	while (!in.eof()) { count += 1; in >> tmp; }
	in.clear();
	in.seekg(0, std::ios::beg);

	for (int i = 0; i < (count / 2); i++)
	{
		Texture *texture = new Texture;
		D3DSURFACE_DESC desc;
		in >> tmp;

		if (FAILED(D3DXCreateTextureFromFileExA(_device, tmp.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
			1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x00000001, 0x00000001, 0x00FF00FF, NULL, NULL, &texture->_texture)))
		{
			MessageBoxA(0, ("Error: " + tmp + " is wrong.").c_str(), "Error!", 0);
			return E_FAIL;
		}
		texture->_texture->GetLevelDesc(0, &desc);
		texture->_width = desc.Width;
		texture->_height = desc.Height;

		in >> tmp;
		_textures.insert(std::make_pair(tmp, texture));
	}

	in.close();

	return S_OK;
}

Texture *ResourceManager::GetTexture(const std::string &name)
{
	return _textures.find(name)->second;
}

HRESULT ResourceManager::LoadShaderMap(char *path)
{
	std::ifstream in;

	in.open(path, std::ios::in);
	if (!in.is_open())
		return E_FAIL;

	std::string tmp;
	int count = 0;
	while (!in.eof()) { count += 1; in >> tmp; }
	in.clear();
	in.seekg(0, std::ios::beg);

	for (int i = 0; i < (count / 2); i++)
	{
		in >> tmp;
		ID3DXEffect *shader;
		D3DXCreateEffectFromFileA(_device, tmp.c_str(), 0, 0, 0, 0, &shader, 0);

		in >> tmp;
		_shaders.insert(std::make_pair(tmp, shader));
	}

	in.close();

	return S_OK;
}

ID3DXEffect *ResourceManager::GetShader(const std::string &name)
{
	return _shaders.find(name)->second;
}

HRESULT ResourceManager::LoadFontMap(char *path)
{
	std::ifstream in;

	in.open(path, std::ios::in);
	if (!in.is_open())
		return E_FAIL;

	std::string tmp;
	int count = 0;
	while (!in.eof()) { count += 1; in >> tmp; }
	in.clear();
	in.seekg(0, std::ios::beg);

	for (int i = 0; i < (count / 2); i++)
	{
		in >> tmp;

		std::string fontpath = tmp;

		//		AddFontResourceExA(tmp.c_str(), FR_PRIVATE, 0);
		//		D3DXCreateFontA(_device, size, 0, 500, 1, false, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, tmp.c_str(), &font);
		//		RemoveFontResourceExA(tmp.c_str(), FR_PRIVATE, 0);

		in >> tmp;
		_fonts.insert(std::make_pair(tmp, fontpath));
	}

	in.close();

	return S_OK;
}

ID3DXFont *ResourceManager::GetFont(const std::string &name, int size)
{
	ID3DXFont *font;

	AddFontResourceExA(_fonts.find(name)->second.c_str(), FR_PRIVATE, 0);
	D3DXCreateFontA(_device, size, 0, 500, 1, false, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, _fonts.find(name)->second.c_str(), &font);
	//D3DXCreateFontA(_device, size, 0, 500, 1, false, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, NULL, "Fixedsys Excelsior", &font);
	RemoveFontResourceExA(_fonts.find(name)->second.c_str(), FR_PRIVATE, 0);

	return font;
}

HRESULT ResourceManager::LoadSEMap(char *path)
{
	std::ifstream in;

	in.open(path, std::ios::in);
	if (!in.is_open())
		return E_FAIL;

	std::string tmp;
	int count = 0;
	while (!in.eof()) { count += 1; in >> tmp; }
	in.clear();
	in.seekg(0, std::ios::beg);

	for (int i = 0; i < (count / 2); i++)
	{
		in >> tmp;

		SE *se = SE::Create(tmp);

		in >> tmp;
		_ses.insert(std::make_pair(tmp, se));
	}

	in.close();

	return S_OK;
}

HRESULT ResourceManager::LoadBGMMap(char *path)
{
	std::ifstream in;

	in.open(path, std::ios::in);
	if (!in.is_open())
		return E_FAIL;

	std::string tmp;
	int count = 0;
	while (!in.eof()) { count += 1; in >> tmp; }
	in.clear();
	in.seekg(0, std::ios::beg);

	for (int i = 0; i < (count / 2); i++)
	{
		in >> tmp;

		BGM *bgm = BGM::Create(tmp, 1, 0);
		in >> tmp;
		_bgms.insert(std::make_pair(tmp, bgm));
	}

	in.close();

	return S_OK;
}
