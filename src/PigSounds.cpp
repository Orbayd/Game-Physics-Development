#include "PigSounds.h"


#include <assert.h>

PigSoundObj::PigSoundObj()
{
	oinkSoundList[0] = "../../data/piglette oink a1.wav";
	oinkSoundList[1] = "../../data/piglette oink a2.wav";
	oinkSoundList[2] = "../../data/piglette oink a3.wav";
	oinkSoundList[3] = "../../data/piglette oink a4.wav";

	oinkSoundList[4] = "../../data/piglette oink a5.wav";
	oinkSoundList[5] = "../../data/pig_hi-hat_1.wav";
	oinkSoundList[6] = "../../data/pig_hi-hat_2.wav";
	oinkSoundList[7] = "../../data/piglette oink a8.wav";
	
	oinkSoundList[8] = "../../data/piglette oink a9.wav";
	oinkSoundList[9] = "../../data/piglette oink a10.wav";
	oinkSoundList[10] = "../../data/piglette oink a11.wav";
	oinkSoundList[11] = "../../data/piglette oink a12.wav";

	deatSound = "../../data/piglette destroyed.wav";

	
}

PigSoundObj::~PigSoundObj()
{
}

void PigSoundObj::Play(SoundType sType)
{
	sType;
	const char * sfile = 0;
	if (sType == SoundType::OINK)
	{
	
		sfile = oinkSoundList[getRndNum(11)];

	}
	else if (sType == SoundType::DEATH)
	{
		sfile = deatSound;
	}
	else
	{
		assert(sfile);
	}
	irrklang::ISound *pSnd = 0;
	pSnd = pSndEngine->play2D(sfile, false, false, true);
	pSnd->drop();

}

PigSoundObj *PigSoundObj::Instance()
{
	static PigSoundObj instance;
	return &instance;
}