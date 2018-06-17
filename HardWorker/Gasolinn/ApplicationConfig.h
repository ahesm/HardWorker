#ifndef _APPLICATIONCONFIG_H_
#define _APPLICATIONCONFIG_H_

#include <io.h>
#include <string>

class ApplicationConfig
{
public:
	std::string _title;
	int _width, _height;

public:
	ApplicationConfig(const std::string &title, int width, int height);

	void MakeTextureMap(const std::string &srcFolder, const std::string &dstFileName, const std::string &dstFolder);
	void LoadTextureMap(char *path);

	void MakeShaderMap(const std::string &srcFolder, const std::string &dstFileName, const std::string &dstFolder);
	void LoadShaderMap(char *path);

	void MakeFontMap(const std::string &srcFolder, const std::string &dstFileName, const std::string &dstFolder);
	void LoadFontMap(char *path);

	void MakeSEMap(const std::string &srcFolder, const std::string &dstFileName, const std::string &dstFolder);
	void LoadSEMap(char *path);

	void MakeBGMMap(const std::string &srcFolder, const std::string &dstFileName, const std::string &dstFolder);
	void LoadBGMMap(char *path);
};

#endif