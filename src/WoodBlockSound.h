#ifndef WOOD_BLOCK_SOUND_H
#define WOOD_BLOCK_SOUND_H
#include "SoundObject.h"
class WoodBlockSoundObj : public SoundObject
{
public:
	WoodBlockSoundObj();
	~WoodBlockSoundObj();
	virtual void Play(SoundType stype)override;
private:
	const char * deathSoundList[3];
	//const char * collisionList[6];
	//const char * damageList[3];
};



#endif