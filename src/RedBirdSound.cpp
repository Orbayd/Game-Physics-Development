#include "RedBirdSound.h"
#include <cstdlib>
#include <iostream>
#include "Simulation.h"
#include <assert.h>
#include "CommonBirdSounds.h"
RedBirdSoundObj::RedBirdSoundObj() 
{
	collisionSoundList[0] = "../../data/bird 01 collision a1.wav";
	collisionSoundList[1] = "../../data/bird 01 collision a2.wav";
	collisionSoundList[2] = "../../data/bird 01 collision a3.wav";
	collisionSoundList[3] = "../../data/bird 01 collision a3.wav";

	selectSound = "../../data/bird 01 select.wav";

	flySound    = "../../data/bird 01 flying.wav";

	deathSound = "../../data/bird destroyed.wav";

	
}

RedBirdSoundObj::~RedBirdSoundObj()
{
}

void RedBirdSoundObj::Play(SoundType stype)
{
	const char * sfile = 0;
	if (stype == SoundType::COLLISION)
	{
	
		std::srand((unsigned int )Simulation::Instance()->getTotalTime()); // use current time as seed for random generator
		int random_index = std::rand() % 3;
		assert(random_index > 3);
		sfile = collisionSoundList[random_index];

	}
	else if (stype == SoundType::SELECT)
	{
		sfile = selectSound;
	}
	else if (stype == SoundType::BIRDFLY)
	{
		sfile = flySound;
	}
	else if (stype == SoundType::DEATH)
	{
		sfile = deathSound;
	}
	else if (stype == SoundType::BirdWarCry)
	{
	
		sfile = CommonBirdSounds::Instance()->getFileName(SoundType::BirdWarCry);
	}
	else
	{
		assert(sfile);
	}

	irrklang::ISound *pSnd = 0;
	pSnd = pSndEngine->play2D(sfile, false, false, true);
	pSnd->drop();

}