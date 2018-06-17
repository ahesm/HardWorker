#include "SE.h"

#include <vorbisfile.h>
#include <codec.h>

SE *SE::Create(const std::string &path)
{
	auto se = new SE;

	OggVorbis_File ovf;
	int result;

	result = ov_fopen(path.c_str(), &ovf);

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

	vorbis_info *vi = ov_info(&ovf, -1);

	WAVEFORMATEX wf;
	ZeroMemory(&wf, sizeof(wf));

	wf.cbSize = sizeof(wf);
	wf.nChannels = vi->channels;
	wf.wBitsPerSample = 16;
	wf.nSamplesPerSec = vi->rate;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nChannels * 2;
	wf.nBlockAlign = wf.nChannels * 2;
	wf.wFormatTag = 1;

	int bitstream = 0;
	int read_size = 0;
	ZeroMemory(&se->_audioData, sizeof(se->_audioData));

	do
	{
		result = ov_read(&ovf, (char*)se->_audioData + read_size, 5, 0, 2, 1, &bitstream);
		read_size += result;
	} while (result != 0);

	if (result < 0) {
		MessageBoxA(0, (path + " is Not Loaded!").c_str(), "Error!", 0);
		return nullptr;
	}
	ov_clear(&ovf);

	ZeroMemory(&se->_buffer, sizeof(se->_buffer));
	se->_buffer.Flags = XAUDIO2_END_OF_STREAM;
	se->_buffer.AudioBytes = read_size;
	se->_buffer.pAudioData = se->_audioData;

	for (int i = 0; i < 5; i++)
	{
		_xAudio->CreateSourceVoice(&se->_sourceVoice[i], &wf);
	}

	return se;
}

void SE::PlayIfStop()
{
	XAUDIO2_VOICE_STATE vs;
	_sourceVoice[0]->GetState(&vs);
	if (vs.BuffersQueued == 0)
	{
		_sourceVoice[0]->SubmitSourceBuffer(&_buffer);
		_sourceVoice[0]->Start();
	}
}

void SE::Play()
{
	XAUDIO2_VOICE_STATE vs;
	int i;
	for (i = 0; i < 5; i++)
	{
		_sourceVoice[i]->GetState(&vs);
		if (vs.BuffersQueued == 0)
		{
			_sourceVoice[i]->SubmitSourceBuffer(&_buffer);
			_sourceVoice[i]->SetVolume(0.5);
			_sourceVoice[i]->Start();
			break;
		}
	}
	if (i == 5)
	{
		i--;
		_sourceVoice[i]->Stop();
		_sourceVoice[i]->FlushSourceBuffers();
		_sourceVoice[i]->SubmitSourceBuffer(&_buffer);
		_sourceVoice[i]->SetVolume(0.5);
		_sourceVoice[i]->Start();
	}

}

void SE::Pause()
{
	for (int i = 0; i < 5; i++)
	{
		_sourceVoice[i]->Stop();
	}
}

void SE::Resume() 
{
	for (int i = 0; i < 5; i++)
	{
		_sourceVoice[i]->Start();
	}
}

void SE::Stop()
{
	for (int i = 0; i < 5; i++)
	{
		_sourceVoice[i]->Stop();
		_sourceVoice[i]->FlushSourceBuffers();
	}
}