#ifndef RED_BIRD_SOUND_H
#define RED_BIRD_SOUND_H
#include "SoundObject.h"
class RedBirdSoundObj : public SoundObject
{
public:
	RedBirdSoundObj();
	~RedBirdSoundObj();
	virtual void Play(SoundType type) override;
private:
	const char * collisionSoundList[4];
	const char * selectSound;
	const char * flySound;
	const char * deathSound;
};



#endif