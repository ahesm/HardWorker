#ifndef _SE_H_
#define _SE_H_

#include <XAudio2.h>

#include "Root.h"

class SE : public Root
{
public:
	IXAudio2SourceVoice *_sourceVoice[5];
	XAUDIO2_BUFFER _buffer;
	BYTE _audioData[1024 * 1024];


public:
	static SE *Create(const std::string &path);

	void PlayIfStop();
	void Play();
	void Pause();
	void Resume();
	void Stop();

};

#endif