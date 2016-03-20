#ifndef SOUNDOBJECT_H
#define SOUNDOBJECT_H

#include "irrKlang.h"
enum SoundType
{
	COLLISION,
	BIRDFLY,
	DEATH,
	SELECT,
	OINK,
	BirdWarCry
};


class SoundObject
{
public:
	virtual void Play(SoundType type) = 0;
	~SoundObject();
	
private:
	
protected:
	SoundObject();
	int  getRndNum(int maxNum);
	irrklang::ISoundEngine	*pSndEngine;
};




#endif