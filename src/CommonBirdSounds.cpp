#include "CommonBirdSounds.h"
#include <cstdlib>
#include <iostream>
#include "Simulation.h"
#include <assert.h>

CommonBirdSounds::CommonBirdSounds()
{
	birdYellList[0] = "../../data/bird misc a1.wav";
	birdYellList[1] = "../../data/bird misc a2.wav";
	birdYellList[2] = "../../data/bird misc a3.wav";
	birdYellList[3] = "../../data/bird misc a4.wav";

	birdYellList[4] = "../../data/bird misc a5.wav";
	birdYellList[5] = "../../data/bird misc a6.wav";
	birdYellList[6] = "../../data/bird misc a7.wav";
	birdYellList[7] = "../../data/bird misc a8.wav";

	birdYellList[8] = "../../data/bird misc a9.wav";
	birdYellList[9] = "../../data/bird misc a10.wav";
	birdYellList[10] = "../../data/bird misc a11.wav";
	birdYellList[11] = "../../data/bird misc a12.wav";
}
CommonBirdSounds::~CommonBirdSounds()
{
}
CommonBirdSounds * CommonBirdSounds::Instance()
{
	static CommonBirdSounds instance;

	return  &instance;

}
const char * CommonBirdSounds::getFileName(SoundType sType)
{
	const char * sfile = 0;
	if (sType == SoundType::BirdWarCry)
	{

		std::srand((unsigned int)Simulation::Instance()->getTotalTime()); // use current time as seed for random generator
		int random_index = std::rand() % 11;
		assert(random_index <= 11);
		sfile = birdYellList[random_index];

	}
	else
	{
		assert(sfile);
	}

	return  sfile;

}
void CommonBirdSounds::Play(SoundType sType)
{

	const char * sfile = 0;
	if (sType == SoundType::BirdWarCry)
	{

		std::srand((unsigned int)Simulation::Instance()->getTotalTime()); // use current time as seed for random generator
		int random_index = std::rand() % 11;
		assert(random_index <= 11);
		sfile = birdYellList[random_index];

	}
	else
	{
		assert(sfile);
	}


	irrklang::ISound *pSnd = 0;
	pSnd = pSndEngine->play2D("../../data/bird 01 flying.wav", false, false, true);
	pSnd->drop();

}
