#include "SoundEngine.h"

SoundEngine *SoundEngine::_instance = NULL;
bool SoundEngine::_isThreadEnd;
CRITICAL_SECTION SoundEngine::_cs;

CriticalSection::CriticalSection(CRITICAL_SECTION *cs)
{
	this->_cs = cs;
	EnterCriticalSection(cs);
}

CriticalSection::~CriticalSection()
{
	LeaveCriticalSection(_cs);
}


SoundEngine::SoundEngine()
{
	_thread = CreateThread(0, 0, StreamingThread, 0, 0, 0);
	InitializeCriticalSection(&_cs);
}

SoundEngine &SoundEngine::GetInstance()
{
	if (_instance == NULL) {
		_instance = new SoundEngine();
	}
	return *_instance;
}

void SoundEngine::Destroy()
{
	CriticalSection cs(&_cs);
	_isThreadEnd = true;
	while (true)
	{
		DWORD exitcode;
		GetExitCodeThread(StreamingThread, &exitcode);
		if (exitcode != STILL_ACTIVE) break;
		Sleep(1);
	}
	for each(auto iterator in ResourceManager::_bgms) {
		if (iterator.second != nullptr) {
			iterator.second->Destroy();
			iterator.second = nullptr;
		}
	}
	ResourceManager::_bgms.clear();

	DeleteCriticalSection(&_cs);

	delete _instance;
	_instance = NULL;
}

DWORD WINAPI SoundEngine::StreamingThread(LPVOID lpParameter)
{
	while (true)
	{
		CriticalSection cs(&_cs);
		if (_isThreadEnd)
		{
			break;
		}
		for each(auto iterator in ResourceManager::_bgms)
		{
			iterator.second->Streaming();
		}
		Sleep(1);
	}
	return 0;
}

void SoundEngine::PlaySE(const std::string &name, bool playIfStop)
{
	if (!ResourceManager::_ses.find(name)->second) return;
	if (playIfStop)
		ResourceManager::_ses.find(name)->second->PlayIfStop();
	else
		ResourceManager::_ses.find(name)->second->Play();
}

void SoundEngine::StopSE(const std::string &name)
{
	if (!ResourceManager::_ses.find(name)->second) return;
	ResourceManager::_ses.find(name)->second->Stop();
}

void SoundEngine::PauseSE(const std::string &name)
{
	if (!ResourceManager::_ses.find(name)->second) return;
	ResourceManager::_ses.find(name)->second->Pause();
}

void SoundEngine::ResumeSE(const std::string &name)
{
	if (!ResourceManager::_ses.find(name)->second) return;
	ResourceManager::_ses.find(name)->second->Resume();
}

void SoundEngine::PlayBGM(const std::string &name)
{
	CriticalSection cs(&_cs);
	ResourceManager::_bgms.find(name)->second->Play();
	ResourceManager::_bgms.find(name)->second->SetVolume(1);
}

void SoundEngine::StopBGM(const std::string &name)
{
	CriticalSection cs(&_cs);
	ResourceManager::_bgms.find(name)->second->Stop();
}

void SoundEngine::PauseBGM(const std::string &name)
{
	CriticalSection cs(&_cs);
	ResourceManager::_bgms.find(name)->second->Pause();
}

void SoundEngine::ResumeBGM(const std::string &name)
{
	CriticalSection cs(&_cs);
	ResourceManager::_bgms.find(name)->second->Resume();
}

void SoundEngine::SetBGMVolume(const std::string &name, float volume)
{
	CriticalSection cs(&_cs);
	ResourceManager::_bgms.find(name)->second->SetVolume(volume);
}