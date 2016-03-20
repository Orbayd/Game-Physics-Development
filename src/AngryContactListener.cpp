#include <assert.h>
#include "PixelToMeter.h"
#include "AzulStopWatch.h"
#include "GameObject2D.h"
#include "AngryContactListener.h"
#include "DebugOut.h"
#include "GameObjectMan.h"
#include "GameSortBucket.h"
#include "Bird.h"
#include "Dead.h"
#include "Flying.h"
#include "SoundMan.h"
#include "World.h"
// need to make this a singleton
extern GameSortBucket *pSortEffects;

extern AzulStopWatch stopWatch;
extern AzulStopWatch totalWatch;

AngryContactListener::AngryContactListener()
	:b2ContactListener()
{
}

AngryContactListener::~AngryContactListener()
{

}

// Called when two fixtures begin to touch.
 void AngryContactListener::BeginContact(b2Contact* pContact) 
{
	pContact;
	GameObject *gObjA = (GameObject *)pContact->GetFixtureA()->GetBody()->GetUserData();
	GameObject *gObjB = (GameObject *)pContact->GetFixtureB()->GetBody()->GetUserData();


	if (gObjA->getName().value == GameObjectName::L1_RedBird || gObjA->getName().value == GameObjectName::Bomb_Particle)
	{
		World::setBalanced();
	//	SoundManager::Play("../../data/wood collision a6.wav");
	}
	if (gObjB->getName().value == GameObjectName::L1_RedBird || gObjB->getName().value == GameObjectName::Bomb_Particle)
	{
		World::setBalanced();
	}
	
}

// Called when two fixtures cease to touch.
void AngryContactListener::EndContact(b2Contact* contact) 
{
	B2_NOT_USED(contact);
}

// This is called after a contact is updated. This allows you to inspect a
// contact before it goes to the solver. If you are careful, you can modify the
// contact manifold (e.g. disable contact).
// A copy of the old manifold is provided so that you can detect changes.
// Note: this is called only for awake bodies.
// Note: this is called even when the number of contact points is zero.
// Note: this is not called for sensors.
// Note: if you set the number of contact points to zero, you will not
// get an EndContact callback. However, you may get a BeginContact callback
// the next step.
void AngryContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) 
{
	B2_NOT_USED(contact);
	B2_NOT_USED(oldManifold);
	//contact->SetEnabled(false);
}

// This lets you inspect a contact after the solver is finished. This is useful
// for inspecting impulses.
// Note: the contact manifold does not include time of impact impulses, which can be
// arbitrarily large if the sub-step is small. Hence the impulse is provided explicitly
// in a separate data structure.
// Note: this is only called for contacts that are touching, solid, and awake.
void AngryContactListener::PostSolve(b2Contact* pContact, const b2ContactImpulse* pImpulse)
{
	pContact;
	// Get the Game Objects
	pImpulse;// Start the show:
	if (World::isBalanced() == false)
	{
		return;
	}
	GameObject *gObjA = (GameObject *)pContact->GetFixtureA()->GetBody()->GetUserData();
	GameObject *gObjB = (GameObject *)pContact->GetFixtureB()->GetBody()->GetUserData();

	// Make sure its OK to cast
	assert(gObjA->HasBody());
	assert(gObjB->HasBody());

	GameObject2D *pObjA = 0;
	GameObject2D *pObjB = 0;

	pObjA = (GameObject2D *)gObjA;
	pObjB = (GameObject2D *)gObjB;

	if (pObjA->name == GameObjectName::L1_RedBird)
	{
		Bird*pBird = (Bird*)pObjA;
		if (pBird->getBirdState() == Fly::GetInstance())
		{
			pBird->ChangeState(Dead::GetInstance());
		}
		
	}
	if (pObjB->name == GameObjectName::L1_RedBird)
	{
		Bird*pBird = (Bird*)pObjB;
		if (pBird->getBirdState() == Fly::GetInstance())
		{
			pBird->ChangeState(Dead::GetInstance());
		}
	}

	// Manifold info
	b2Manifold *pManifold = pContact->GetManifold();
	assert(pManifold);
	int numPoints = pManifold->pointCount;
	assert(numPoints <= 2);


	// World Manifold
	b2WorldManifold WorldManifold;
	pContact->GetWorldManifold(&WorldManifold);

	//out("post: A:%x B:%x %d(%f,%f)\n", pObjA->name, pObjB->name, pImpulse->count, pImpulse->normalImpulses[0], pImpulse->normalImpulses[1]);

	float PunchThroughA = 0.0f;
	float PunchThroughB = 0.0f;

	// Apply the maximum damage allowed, no punch through
	for (int i = 0; i < pImpulse->count; i++)
	{
		float DamageA;
		float DamageB;
		assert(pImpulse->normalImpulses[i] >= 0.0f);

		// Clamp the maximum damage
		if (pObjA->PendingLifeLeft() - pImpulse->normalImpulses[i] < 0.0f)
		{
			// punch through
			DamageA = pObjA->PendingLifeLeft();
			PunchThroughA += pImpulse->normalImpulses[i] - DamageA;

				// apply damage - no matter what, its a punch through
			pObjA->AddDamage(DamageA);
			
		}
		else
		{
			DamageA = pImpulse->normalImpulses[i];

			if (DamageA > 20.0f)
			{
				pObjA->AddDamage(DamageA);
			}
		}

		// Clamp the maximum damage
		if (pObjB->PendingLifeLeft() - pImpulse->normalImpulses[i] < 0.0f)
		{
			// punch through
			DamageB = pObjB->PendingLifeLeft();
			PunchThroughB += pImpulse->normalImpulses[i] - DamageB ;
			// apply damage - no matter what, its a punch through
			pObjB->AddDamage(DamageB);
			
		}
		else
		{
			DamageB = pImpulse->normalImpulses[i];

			if (DamageB > 20.0f)
			{
				pObjB->AddDamage(DamageB);
			}
		}

	}

	// Punch through
	if (PunchThroughA > 0.0f && pObjA->pBody->GetType() != b2_staticBody)
	{
		for (int i = 0; i < pImpulse->count; i++)
		{
			//pObjB->pBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
 			b2Vec2 NormImpulse = -PunchThroughA * WorldManifold.normal;
			//out("   punchA: %d: (%f,%f)\n", i, NormImpulse.x, NormImpulse.y);
			out("Speed Bfirst: %d: (%f,%f)\n", i, pObjB->pBody->GetLinearVelocity().x, pObjB->pBody->GetLinearVelocity().x);
			if (pObjB->name == GameObjectName::L1_RedBird){
				pObjB->pBody->ApplyLinearImpulse(NormImpulse, WorldManifold.points[i], true);
			}
			out("Speed Blater: %d: (%f,%f)\n", i, pObjB->pBody->GetLinearVelocity().x, pObjB->pBody->GetLinearVelocity().x);
		}
	}

	if (PunchThroughB > 0.0f && pObjB->pBody->GetType() != b2_staticBody)
	{
		for (int i = 0; i < pImpulse->count; i++)
		{
			//pObjA->pBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			b2Vec2 NormImpulse = PunchThroughB * WorldManifold.normal;
			//out("   punchB: %d: (%f,%f)\n", i, NormImpulse.x, NormImpulse.y);
			out("Speed Afirst: %d: (%f,%f)\n", i, pObjB->pBody->GetLinearVelocity().x, pObjB->pBody->GetLinearVelocity().x);
			if (pObjA->name == GameObjectName::L1_RedBird){
				pObjA->pBody->ApplyLinearImpulse(NormImpulse, WorldManifold.points[i], true);
			}
			out("Speed Alater: %d: (%f,%f)\n", i, pObjB->pBody->GetLinearVelocity().x, pObjB->pBody->GetLinearVelocity().x);
		}
	}
}
