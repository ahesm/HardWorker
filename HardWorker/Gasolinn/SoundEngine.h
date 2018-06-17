#ifndef _SOUNDENGINE_H_
#define _SOUNDENGINE_H_

#include "Root.h"
#include "ResourceManager.h"

class CriticalSection
{
private:
	CRITICAL_SECTION *_cs;

public:
	CriticalSection(CRITICAL_SECTION *cs);
	~CriticalSection();
};

class SoundEngine : public Root
{
private:
	static SoundEngine *_instance;

public:
	SoundEngine();
	HANDLE _thread;
	static bool _isThreadEnd;
	static CRITICAL_SECTION _cs;

public:
	static SoundEngine &GetInstance();
	static void Destroy();

public:
	static void PlaySE(const std::string &name, bool playifStop);
	static void StopSE(const std::string &name);
	static void PauseSE(const std::string &name);
	static void ResumeSE(const std::string &name);

public:
	static void PlayBGM(const std::string &name);
	static void StopBGM(const std::string &name);
	static void PauseBGM(const std::string &name);
	static void ResumeBGM(const std::string &name);
	static void SetBGMVolume(const std::string &name, float volume);

	static DWORD WINAPI StreamingThread(LPVOID lpParameter);

};

#endif