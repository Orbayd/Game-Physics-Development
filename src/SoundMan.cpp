#include "SoundMan.h"
SoundManager::SoundManager()
{
	pSndEngine = irrklang::createIrrKlangDevice();
}

SoundManager::~SoundManager()
{
}
void SoundManager::Create()
{
	SoundManager::GetInstance();
	
}
SoundManager* SoundManager::GetInstance()
{
	static SoundManager instance;
	return &instance;
}
void SoundManager::Play(const char* soundFile)
{
	SoundManager * instance = SoundManager::GetInstance();
	irrklang::ISound *pSnd = 0;
	pSnd = instance->pSndEngine->play2D(soundFile, false, false, true);
	pSnd->drop();

}
 irrklang::ISoundEngine* SoundManager::getSoundEngine()
{
	SoundManager * instance = SoundManager::GetInstance();
	return instance->pSndEngine;
}