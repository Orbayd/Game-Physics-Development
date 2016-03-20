#ifndef COMMON_BIRD_SOUND_H
#define COMMON_BIRD_SOUND_H
#include "SoundObject.h"
class CommonBirdSounds :public SoundObject
{
public:
	
	~CommonBirdSounds();
	static CommonBirdSounds * Instance();
	virtual void Play(SoundType type) override;
	const char * getFileName(SoundType type);
private:
	const char * birdYellList[12];
	CommonBirdSounds();
};


#endif