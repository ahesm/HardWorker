#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <map>
#include <string>

#include "Root.h"
#include "SE.h"
#include "BGM.h"

typedef std::map<std::string, SE *> SEMap;
typedef std::map<std::string, BGM *> BGMMap;

class ResourceManager : public Root
{
public:
	static TextureMap _textures;
	static ShaderMap _shaders;
	static FontMap _fonts;
	static SEMap _ses;
	static BGMMap _bgms;

public:
	static HRESULT LoadTextureMap(char *path);
	static Texture *GetTexture(const std::string &name);

	static HRESULT LoadShaderMap(char *path);
	static ID3DXEffect *GetShader(const std::string &name);

	static HRESULT LoadFontMap(char *path);
	static ID3DXFont *GetFont(const std::string &name, int size);

	static HRESULT LoadSEMap(char *path);

	static HRESULT LoadBGMMap(char *path);


};

#endif