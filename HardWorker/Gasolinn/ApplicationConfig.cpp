#include "ApplicationConfig.h"

#include <Windows.h>
#include <stdio.h>
#include <fstream>

#include "ResourceManager.h"

ApplicationConfig::ApplicationConfig(const std::string &title, int width, int height)
{
	_title = title;
	_width = width;
	_height = height;
}

void ApplicationConfig::MakeTextureMap(const std::string &srcFolder, const std::string &dstFileName, const std::string &dstFolder)
{
	std::ofstream out((dstFolder + "\\" + dstFileName + ".map").c_str());

	_finddata_t fd;
	long handle = _findfirst((srcFolder + "\\*.png").c_str(), &fd);

	if (handle == -1)
		return;

	do
	{
		std::string tag = fd.name;
		tag = tag.substr(0, tag.find("."));

		out << srcFolder + "\\" + fd.name << " " << tag << std::endl;
	} while (_findnext(handle, &fd) != -1);

	_findclose(handle);

	out.close();
}

void ApplicationConfig::LoadTextureMap(char *path)
{
	if (FAILED(ResourceManager::LoadTextureMap(path)))
	{
		MessageBoxA(0, "TexutureMap not loaded", "Error!", 0);
		return;
	}
}

void ApplicationConfig::MakeShaderMap(const std::string &srcFolder, const std::string &dstFileName, const std::string &dstFolder)
{
	std::ofstream out((dstFolder + "\\" + dstFileName + ".map").c_str());

	_finddata_t fd;
	long handle = _findfirst((srcFolder + "\\*.fx").c_str(), &fd);

	if (handle == -1)
		return;

	do
	{
		std::string tag = fd.name;
		tag = tag.substr(0, tag.find("."));

		out << srcFolder + "\\" + fd.name << " " << tag << std::endl;
	} while (_findnext(handle, &fd) != -1);

	_findclose(handle);

	out.close();
}

void ApplicationConfig::LoadShaderMap(char *path)
{
	if (FAILED(ResourceManager::LoadShaderMap(path)))
	{
		MessageBoxA(0, "ShaderMap not loaded", "Error!", 0);
		return;
	}
}

void ApplicationConfig::MakeFontMap(const std::string &srcFolder, const std::string &dstFileName, const std::string &dstFolder)
{
	std::ofstream out((dstFolder + "\\" + dstFileName + ".map").c_str());

	_finddata_t fd;
	long handle = _findfirst((srcFolder + "\\*.ttf").c_str(), &fd);

	if (handle == -1)
		return;

	do
	{
		std::string tag = fd.name;
		tag = tag.substr(0, tag.find("."));

		out << srcFolder + "\\" + fd.name << " " << tag << std::endl;
	} while (_findnext(handle, &fd) != -1);

	_findclose(handle);

	out.close();
}

void ApplicationConfig::LoadFontMap(char *path)
{
	if (FAILED(ResourceManager::LoadFontMap(path)))
	{
		MessageBoxA(0, "FontMap not loaded", "Error!", 0);
		return;
	}
}

void ApplicationConfig::MakeSEMap(const std::string &srcFolder, const std::string &dstFileName, const std::string &dstFolder)
{
	std::ofstream out((dstFolder + "\\" + dstFileName + ".map").c_str());

	_finddata_t fd;
	long handle = _findfirst((srcFolder + "\\*.ogg").c_str(), &fd);

	if (handle == -1)
		return;

	do
	{
		std::string tag = fd.name;
		tag = tag.substr(0, tag.find("."));

		out << srcFolder + "\\" + fd.name << " " << tag << std::endl;
	} while (_findnext(handle, &fd) != -1);

	_findclose(handle);

	out.close();
}

void ApplicationConfig::LoadSEMap(char *path)
{
	if (FAILED(ResourceManager::LoadSEMap(path)))
	{
		MessageBoxA(0, "SEMap not loaded", "Error!", 0);
		return;
	}
}

void ApplicationConfig::MakeBGMMap(const std::string &srcFolder, const std::string &dstFileName, const std::string &dstFolder)
{
	std::ofstream out((dstFolder + "\\" + dstFileName + ".map").c_str());

	_finddata_t fd;
	long handle = _findfirst((srcFolder + "\\*.ogg").c_str(), &fd);

	if (handle == -1)
		return;

	do
	{
		std::string tag = fd.name;
		tag = tag.substr(0, tag.find("."));

		out << srcFolder + "\\" + fd.name << " " << tag << std::endl;
	} while (_findnext(handle, &fd) != -1);

	_findclose(handle);

	out.close();
}

void ApplicationConfig::LoadBGMMap(char *path)
{
	if (FAILED(ResourceManager::LoadBGMMap(path)))
	{
		MessageBoxA(0, "BGMMap not loaded", "Error!", 0);
		return;
	}
}