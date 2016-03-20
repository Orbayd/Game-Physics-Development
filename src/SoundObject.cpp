#include "SoundObject.h"
#include <cstdlib>
#include "Simulation.h"
#include <assert.h>
#include "SoundMan.h"
SoundObject::SoundObject()
{
	pSndEngine = SoundManager::getSoundEngine();
}

SoundObject::~SoundObject()
{
}
int SoundObject::getRndNum(int maxnum)
{
	std::srand((unsigned int)Simulation::Instance()->getTotalTime()); // use current time as seed for random generator
	int random_index = std::rand() % maxnum;
	assert(random_index <= maxnum);
	
	return random_index;
}