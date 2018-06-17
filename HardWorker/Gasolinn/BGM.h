#ifndef _BGM_H_
#define _BGM_H_

#include "Root.h"

#include <vorbisfile.h>
#include <codec.h>

#define MAX_BUFFER_SIZE 102400
#define BUFFER_NUM 3

class BGM : public Root
{
public:
	OggVorbis_File _ovf;
	IXAudio2SourceVoice *_sourceVoice;
	XAUDIO2_BUFFER _buffer[BUFFER_NUM];
	BYTE _audioData[BUFFER_NUM][MAX_BUFFER_SIZE];

	long _loopStart = 0;
	int _bufferIndex = 0;

	bool _isLoop = false;
	bool _isPlaying = false;
	bool _isPausing = false;
	bool _isLoopback = false;

public:
	static BGM *Create(const std::string &path, bool loop, long loopStart);

	void Destroy();

	void Streaming();

	void Play();
	void Stop();
	void Pause();
	void Resume();
	
	void SetVolume(float volume);

};

#endif