#ifndef SOUNDMAN_H
#define SOUNDMAN_H
#include "irrKlang.h"
class SoundManager
{
public:
	
	~SoundManager();
	static void Create();
	static void Play(const  char * file);
	static irrklang::ISoundEngine	* getSoundEngine();
private:
	static SoundManager* GetInstance();
	SoundManager();
	// Todo, put these into a container?
	irrklang::ISoundEngine	*pSndEngine;
	irrklang::ISound		*pSndTheme;
};




#endif