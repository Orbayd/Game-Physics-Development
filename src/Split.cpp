#include "Split.h"
#include "Bird.h"
#include "BombEmitter.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"

#include "BlueBird.h"

#include "PixelToMeter.h"
#include "Level.h"
#include "SmokeTrailMan.h"
Split::Split()
{

}

Split::~Split()
{
}

void Split::Execute(Bird * pbird)
{
	pbird;
 	b2Vec2 birdLinVel = pbird->pBody->GetLinearVelocity();
	b2Vec2 faceDirection = birdLinVel;
	faceDirection.Normalize();
	
	b2Vec2 lkc = birdLinVel;
	birdLinVel.Normalize();
	
	
	faceDirection *= PixelToMeter(pbird->origWidth*8.0f);
	
	birdLinVel *= PixelToMeter(pbird->origWidth*2.0f);
	b2Vec2 perp,perp2;
	
	perp.Set(birdLinVel.y, -1 * birdLinVel.x);
	perp2.Set(-1 * birdLinVel.y, birdLinVel.x);
	perp += pbird->pBody->GetPosition();
	


	b2Vec2 n = pbird->pBody->GetPosition() - faceDirection;
	//Bird * pbird3 = BlueBird::Copy(GameObjectName::L1_RedBird, pbird, b2Vec2(MeterToPixel(n.x), MeterToPixel(n.y)));
	//pbird3;*/


	Bird * pbird1 = BlueBird::Copy(GameObjectName::L1_RedBird, pbird, b2Vec2(MeterToPixel(perp.x), MeterToPixel(perp.y ) ));
	b2Vec2 velbird1 = pbird1->pBody->GetPosition() - n;
	
	float scalar = lkc.Length();
	
	velbird1.Normalize();
	velbird1 *= scalar;
	pbird1->pBody->SetLinearVelocity(velbird1);
	
	//Sprite angle
	//float angle = pbird1->pBody->GetAngle();
	//angle += 30.0f * DEGTORAD;
	//pbird1->pBody->SetTransform(pbird1->pBody->GetPosition(), angle);

	
	
	perp2 += pbird->pBody->GetPosition();
	Bird * pbird2 = BlueBird::Copy(GameObjectName::L1_RedBird, pbird, b2Vec2(MeterToPixel(perp2.x), MeterToPixel(perp2.y)));
	

	b2Vec2 velbird2 = pbird2->pBody->GetPosition() - n;
	velbird2.Normalize();
	velbird2 *= scalar;
	pbird2->pBody->SetLinearVelocity(velbird2);

	////sprite angle
	//angle = pbird2->pBody->GetAngle();
	//angle += 30.0f * DEGTORAD;
	//pbird2->pBody->SetTransform(pbird2->pBody->GetPosition(), angle);
	SmokeManager::AddSmoke(pbird);
}

Split* Split::getInstance()
{
	static Split instance;
	return &instance;


}