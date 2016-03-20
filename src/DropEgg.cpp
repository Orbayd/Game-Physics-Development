#include "DropEgg.h"
#include "Bird.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "EggEmitter.h"
#include "SmokeTrailMan.h"
DropEgg::DropEgg()
{
	GameSortBucket *pSortParticles = (GameSortBucket*)GameObjectMan::Find(GameObjectName::Effects_Sort);
	pEmitter = new EggEmitter(GameObjectName::Bomb_Particle, Rect(400.0f, 500.0f, 45.0f *0.80f, 57 * 0.80f), pSortParticles, ImageName::Egg);

}

DropEgg::~DropEgg()
{
}

void DropEgg::Execute(Bird * pbird)
{

	
	b2Vec2 eegVel( 0, -40.0f);
	pbird->pBody->ApplyLinearImpulse(2*-eegVel , pbird->pBody->GetWorldCenter(), true);
	pbird->pBody->GetFixtureList()->SetDensity(1.0f);
	pbird->pBody->ResetMassData();

	pEmitter->SetCenter(b2Vec2(pbird->posX, pbird->posY));
	pEmitter->Spawn(5, ImageName::Egg, 1, eegVel, 0.0f, 0.0f);
	pbird->getGraphicsObject()->SetImage(ImageName::WhiteBirdAbility);
	SmokeManager::AddSmoke(pbird);
}

DropEgg* DropEgg::getInstance()
{
	static DropEgg instance;
	return &instance;


}