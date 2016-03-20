#ifndef BIRD_H
#define BIRD_H
#include "AzulStopWatch.h"
#include "GameObject2D.h"
#include "GameSortBucket.h"
#include "BirdState.h"

#include "BirdAbility.h"

#include "SoundObject.h"

class ParticleEmitter;
class TrailEmitter;
class Bird : public GameObject2D
{
public:
	// Create
	Bird(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort);
	virtual ~Bird();
	virtual void WorldUpdate(float currentTime) override;
	
	void ChangeState(BirdState* pbirdState);
	void LostAbility();
	void ExecuteAbility();

	
	virtual void AddJumpEvent();
	virtual void AddBlinkEvent() = 0;
	virtual void PlayWarCry() = 0;
	virtual void ChangeSpriteToFly() = 0;
	virtual void ChangeSpriteToDeath() = 0;

	virtual void DeadPhase();
	virtual void SpawnFeathers();
	virtual void AddDamage(float normalImpulse);
	SoundObject * pBirdSdnObj;
	BirdState* getBirdState();
	TrailEmitter * pTrailEmitter;
private:
	Bird();	
	ParticleEmitter *pFeatherEmitter;
	ParticleEmitter *pSmokeEmitter;
	bool featherFlag;
protected:
	
	BirdState* pbirdState;
	Ability *pAbility;
	
};

#endif