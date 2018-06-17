#include "BGM.h"

BGM *BGM::Create(const std::string &path, bool loop, long loopStart)
{
	auto bgm = new BGM;

	int result = ov_fopen(path.c_str(), &bgm->_ovf);

	if (result != 0) {
		switch (result) {
		case OV_EREAD:
			MessageBoxA(0, "OV_EREAD", "Error!", 0);
			break;
		case OV_ENOTVORBIS:
			MessageBoxA(0, "OV_ENOTVORBIS", "Error!", 0);
			break;
		case OV_EVERSION:
			MessageBoxA(0, "OV_EVERSION", "Error!", 0);
			break;
		case OV_EBADHEADER:
			MessageBoxA(0, "OV_EBADHEADER", "Error!", 0);
			break;
		case OV_EFAULT:
			MessageBoxA(0, "OV_EFAULT", "Error!", 0);
			break;
		default:
			MessageBoxA(0, "DEFAULT", "Error!", 0);
		}

		return nullptr;
	}

	vorbis_info *vi = ov_info(&bgm->_ovf, -1);

	WAVEFORMATEX wf;
	ZeroMemory(&wf, sizeof(wf));

	wf.cbSize = sizeof(wf);
	wf.nChannels = vi->channels;
	wf.wBitsPerSample = 16;
	wf.nSamplesPerSec = vi->rate;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nChannels * 2;
	wf.nBlockAlign = wf.nChannels * 2;
	wf.wFormatTag = 1;

	// 보이스 생성
	_xAudio->CreateSourceVoice(&bgm->_sourceVoice, &wf);

	bgm->_isLoop = loop;
	bgm->_loopStart = loopStart;

	return bgm;
}

void BGM::Destroy()
{
	_sourceVoice->DestroyVoice();
	_sourceVoice = nullptr;
	ov_clear(&_ovf);

	delete this;
}

void BGM::Streaming()
{
	if (!_isPlaying) return;

	XAUDIO2_VOICE_STATE state;
	_sourceVoice->GetState(&state);
	if (state.BuffersQueued < BUFFER_NUM)
	{
		// 루프한다면
		if (_isLoopback)
		{
			ov_pcm_seek(&_ovf, _loopStart);
			_isLoopback = false;
		}

		// 파일을 읽는다.
		int bitstream = 0;
		int read_size = 0;	// 읽은 양
		int result = 0;
		ZeroMemory(&_audioData[_bufferIndex], sizeof(_audioData[_bufferIndex]));

		do
		{
			result = ov_read(&_ovf, (char*)_audioData[_bufferIndex] + read_size, MAX_BUFFER_SIZE - read_size
				, 0, 2, 1, &bitstream);
			read_size += result;	// 일반적으로 result는 읽은 바이트 값이다.
		} while (result > 0 && read_size < MAX_BUFFER_SIZE);	// EOF(0)또는 최대 버퍼 크기까지 읽는다.

		// result 값이 음수라면 에러
		if (result < 0)
		{
			switch (result)
			{
			case OV_HOLE:
				MessageBoxA(0, "OV_HOLE", "Error!", 0);
				break;
			case OV_EBADLINK:
				MessageBoxA(0, "OV_EBADLINK", "Error!", 0);
				break;
			case OV_EINVAL:
				MessageBoxA(0, "OV_EINVAL", "Error!", 0);
				break;
			default:
				MessageBoxA(0, "DEFAULT", "Error!", 0);
			}
		}

		// EOF를 만나면 루프 백
		if (result == 0 && _isLoop)
		{
			_isLoopback = true;
		}

		// 버퍼 생성
		ZeroMemory(&_buffer[_bufferIndex], sizeof(_buffer[_bufferIndex]));
		_buffer[_bufferIndex].AudioBytes = read_size;
		_buffer[_bufferIndex].pAudioData = _audioData[_bufferIndex];
		if (result != 0 && !_isLoop)
		{
			_buffer[_bufferIndex].Flags = XAUDIO2_END_OF_STREAM;
		}

		_sourceVoice->SubmitSourceBuffer(&_buffer[_bufferIndex]);

		_bufferIndex = (_bufferIndex + 1) % BUFFER_NUM;	
	}
}

void BGM::Play()
{
	if (_isPlaying && !_isPausing) return;
	Stop();
	_isPlaying = true;
	_isPausing = false;
	_sourceVoice->Start();
}

void BGM::Pause()
{
	if (!_isPlaying) return;
	_isPlaying = false;
	_isPausing = true;
	_sourceVoice->Stop();
}

void BGM::Resume()
{
	if (!_isPausing) return;
	_isPlaying = true;
	_isPausing = false;
	_sourceVoice->Start();
}

void BGM::Stop()
{
	if (!_isPlaying && !_isPausing) return;
	_isPlaying = false;
	_isPausing = false;
	_sourceVoice->Stop();
	_sourceVoice->FlushSourceBuffers();
	ov_pcm_seek(&_ovf, 0);
	Streaming();
}

void BGM::SetVolume(float volume)
{
	_sourceVoice->SetVolume(volume);
}