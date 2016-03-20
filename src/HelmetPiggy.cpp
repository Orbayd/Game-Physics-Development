#include "HelmetPiggy.h"
#include "PiggyFactory.h"
#include "Helmet.h"
#include "PixelToMeter.h"
#include "World.h"
Piggy * HelmetPiggy::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect)
{
	Helmet *pHelmet = Helmet::Create(gObjName, ImageName::Helmet, Rect(0, 0, 85*0.8, 40*0.8));
	Piggy * pPig = PiggyFactory::Create(gObjName, imageName, rect);
	pPig->maxDamage = 100.0f;
	pHelmet->SetPosition(pPig->posX, pPig->posY + 30);

	b2WeldJointDef distanceJointDef;
	distanceJointDef.bodyA = pHelmet->pBody;
	distanceJointDef.bodyB = pPig->pBody;
	distanceJointDef.localAnchorA.Set(PixelToMeter(0), PixelToMeter(-30));
	distanceJointDef.localAnchorB.Set(PixelToMeter(0), PixelToMeter(0));

	World::getWorld()->CreateJoint(&distanceJointDef);

	return pPig;
}