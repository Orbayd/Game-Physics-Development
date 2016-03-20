#include "GlassBlockSound.h"
#include <cstdlib>

#include "Simulation.h"
#include <assert.h>
GlassBlockSoundObj::GlassBlockSoundObj()
{
	deathSoundList[0] = "../../data/jewel_break_01.wav";
	deathSoundList[1] = "../../data/jewel_break_02.wav";
	deathSoundList[2] = "../../data/jewel_break_03.wav";


}

GlassBlockSoundObj::~GlassBlockSoundObj()
{
}

void GlassBlockSoundObj::Play(SoundType sType)
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