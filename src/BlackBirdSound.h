#ifndef BLACK_BIRD_SOUND_H
#define BLACK_BIRD_SOUND_H
#include "SoundObject.h"
class BlackBirdSoundObj : public SoundObject
{
public:
	BlackBirdSoundObj();
	~BlackBirdSoundObj();
	virtual void Play(SoundType type) override;
private:
	const char * collisionSoundList[4];
	const char * selectSound;
	const char * flySound;
	const char * deathSound;
};

#endif