#pragma once
#include <vector>
#include <AL\al.h>
#include <sndfile.h>
#include "SoundEffectSource.h"
#include <unordered_map>
#include "SoundMusicSource.h"

namespace AA {

struct MusicStream {
	ALuint buffers[4];
	SNDFILE* sndfile;
	SF_INFO sfinfo;
	short* membuf;
	ALenum format;
};

/// <summary>
/// Stores reference access to the loaded sound buffers.
/// addSoundEffect(...) returns id to play the sound.
/// Use SoundSource::Play(...) on the id to play the sound.
/// </summary>
class SoundBufferManager
{
public:
	static SoundBufferManager* get();

	ALuint addSoundEffect(const char* filename);
	bool removeSoundEffect(const ALuint& buffer);

	uint32_t addLongPlaySound(const char* filename);
	//bool removeLongPlaySound(const uint32_t id);
	
	friend class SoundMusicSource;

private:
	SoundBufferManager();
	~SoundBufferManager();
	
	// sound effect buffers so we know what to clean up and whatnot
	std::vector<ALuint> p_SoundEffectBuffers;

	// samples of music or long sounds that would need a buffer
	static const int NUM_MUSIC_BUFFERS = 4;
	static const int BUFFER_SAMPLES = 8192;

	int StartLongSoundPlay(const uint32_t id, const ALuint src);
	int PauseLongSoundPlay(const uint32_t id, const ALuint src);
	int StopLongSoundPlay(const uint32_t id, const ALuint src);

	// long sound buffers so we know how to stream and clean up



	//StreamPlayer *p_StreamPlayer;


};
} // end namespace AA
