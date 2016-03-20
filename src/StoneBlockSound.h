#ifndef STONE_BLOCK_SOUND_H
#define STONE_BLOCK_SOUND_H
#include "SoundObject.h"
class StoneBlockSoundObj : public SoundObject
{
public:
	StoneBlockSoundObj();
	~StoneBlockSoundObj();
	virtual void Play(SoundType stype)override;
private:
	const char * deathSoundList[3];
	//const char * collisionList[6];
	//const char * damageList[3];
};



#endif