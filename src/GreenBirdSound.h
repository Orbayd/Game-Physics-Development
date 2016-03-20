#ifndef GREEN_BIRD_SOUND_H
#define GREEN_BIRD_SOUND_H
#include "SoundObject.h"
class GreenBirdSoundObj : public SoundObject
{
public:
	GreenBirdSoundObj();
	~GreenBirdSoundObj();
	virtual void Play(SoundType type) override;
private:
	const char * collisionSoundList[4];
	const char * selectSound;
	const char * flySound;
	const char * deathSound;
};

#endif