#ifndef PIG_SOUNDS_H
#define PIG_SOUNDS_H
#include "SoundObject.h"
class PigSoundObj : public SoundObject
{
public:
	PigSoundObj();
	~PigSoundObj();
	virtual void Play(SoundType stype)override;
	static PigSoundObj * Instance();
private:
	const char * oinkSoundList[12];
	const char * deatSound;
	//const char * collisionList[6];
	//const char * damageList[3];
};



#endif