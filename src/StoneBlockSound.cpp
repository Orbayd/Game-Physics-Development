#include "StoneBlockSound.h"
#include <cstdlib>

#include "Simulation.h"
#include <assert.h>
StoneBlockSoundObj::StoneBlockSoundObj()
{
	deathSoundList[0] = "../../data/rock destroyed a1.wav";
	deathSoundList[1] = "../../data/rock destroyed a2.wav";
	deathSoundList[2] = "../../data/rock destroyed a3.wav";


}

StoneBlockSoundObj::~StoneBlockSoundObj()
{
}

void StoneBlockSoundObj::Play(SoundType sType)
{
	sType;
	const char * sfile = 0;
	if (sType == SoundType::DEATH)
	{
		std::srand((unsigned int)Simulation::Instance()->getTotalTime()); // use current time as seed for random generator
		int random_index = std::rand() % 2;
		assert(random_index <= 2);
		sfile = deathSoundList[random_index];

	}
	else
	{

	}
	irrklang::ISound *pSnd = 0;
	pSnd = pSndEngine->play2D(sfile, false, false, true);
	pSnd->drop();

}