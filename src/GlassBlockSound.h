#ifndef GLASS_BLOCK_SOUND_H
#define GLASS_BLOCK_SOUND_H
#include "SoundObject.h"
class GlassBlockSoundObj : public SoundObject
{
public:
	GlassBlockSoundObj();
	~GlassBlockSoundObj();
	virtual void Play(SoundType stype)override;
private:
	const char * deathSoundList[3];
	//const char * collisionList[6];
	//const char * damageList[3];
};



#endif