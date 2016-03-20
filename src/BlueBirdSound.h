#ifndef BLUE_BIRD_SOUND_H
#define BLUE_BIRD_SOUND_H
#include "SoundObject.h"
class BlueBirdSoundObj : public SoundObject
{
public:
	BlueBirdSoundObj();
	~BlueBirdSoundObj();
	virtual void Play(SoundType type) override;
private:
	const char * collisionSoundList[4];
	const char * selectSound;
	const char * flySound;
	const char * deathSound;
};

#endif