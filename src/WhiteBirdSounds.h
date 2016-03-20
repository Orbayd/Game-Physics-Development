#ifndef WHITE_BIRD_SOUND_H
#define WHITE_BIRD_SOUND_H
#include "SoundObject.h"
class WhiteBirdSoundObj : public SoundObject
{
public:
	WhiteBirdSoundObj();
	~WhiteBirdSoundObj();
	virtual void Play(SoundType type) override;
private:
	const char * collisionSoundList[4];
	const char * selectSound;
	const char * flySound;
	const char * deathSound;
};



#endif