#ifndef YELLOW_BIRD_SOUND_H
#define YELLOW_BIRD_SOUND_H
#include "SoundObject.h"
class YellowBirdSoundObj : public SoundObject
{
public:
	YellowBirdSoundObj();
	~YellowBirdSoundObj();
	virtual void Play(SoundType type) override;
private:
	const char * collisionSoundList[4];
	const char * selectSound;
	const char * flySound;
	const char * deathSound;
};

#endif