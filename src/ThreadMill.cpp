#include "ThreadMill.h"
#include "GameObjectMan.h"
#include "BlockFactory.h"
#include "PixelToMeter.h"
#include "World.h"
#include "RedBird.h"
#include "StoneBall.h"
#include "Level.h"
ThreadMill::~ThreadMill()
{
}
ThreadMill::ThreadMill(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort) :GameObject2D(name, pSprite)
{
	GameObjectMan::Add(this, pSort);


}

ThreadMill* ThreadMill::Create(GameObjectName::Name gObjName, Vect &pos,float rotatePos)
{
	GameSortBucket * pGround = (GameSortBucket *)GameObjectMan::Find(GameObjectName::StaticObjects_Sort);
	GameObject2D * pStatic = (GameObject2D*)pGround->getChild();

	GameObject2D *p3;
	GameObject2D *p4; p4;
	p3 = StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(pos[x], pos[y], 35, 35), b2BodyType::b2_dynamicBody);
	p3->pBody->SetAngularVelocity(10.0f);

	// Demo: how to change density
	b2Fixture *pFix3 = p3->pBody->GetFixtureList();
	pFix3->SetDensity(1.0f);
	p3->pBody->ResetMassData();

	p4 = StoneBall::Create(GameObjectName::Block, ImageName::StoneBall_Healty, Rect(pos[x]+100.0f, pos[y], 35, 35), b2BodyType::b2_dynamicBody);
	//p4->pBody->SetAngularVelocity(10.0f);
	//// Demo: how to change density
	b2Fixture *pFix4 = p4->pBody->GetFixtureList();
	pFix4->SetDensity(1.0f);
	p4->pBody->ResetMassData();



	b2RevoluteJointDef revoluteJointDef3;
	//revoluteJointDef3.bodyA = pGround->pBody;
	revoluteJointDef3.bodyA = pStatic->pBody;
	revoluteJointDef3.bodyB = p3->pBody;
	revoluteJointDef3.collideConnected = false;
	//revoluteJointDef3.localAnchorA.Set(PixelToMeter(-1430), PixelToMeter(455));
	revoluteJointDef3.localAnchorA.Set(PixelToMeter(p3->posX- 2480), PixelToMeter(p3->posY-45));
	revoluteJointDef3.localAnchorB.Set(PixelToMeter(0.0f), PixelToMeter(0.0f));
	revoluteJointDef3.userData = 0;

	revoluteJointDef3.enableMotor = true;
	revoluteJointDef3.maxMotorTorque = 30;
	revoluteJointDef3.motorSpeed = rotatePos * 360 * DEGTORAD; //1 turn per second counter-clockwise


	b2RevoluteJoint *joint3 = (b2RevoluteJoint *)World::getWorld()->CreateJoint(&revoluteJointDef3);
	joint3;


	b2RevoluteJointDef revoluteJointDef4;
	//revoluteJointDef4.bodyA = pGround->pBody;
	revoluteJointDef4.bodyA = pStatic->pBody;
	revoluteJointDef4.bodyB = p4->pBody;
	revoluteJointDef4.collideConnected = false;
	revoluteJointDef4.localAnchorA.Set(PixelToMeter(p4->posX - 2480), PixelToMeter(p4->posY - 45));
	revoluteJointDef4.localAnchorB.Set(PixelToMeter(0.0f), PixelToMeter(0.0f));
	revoluteJointDef4.userData = 0;



	b2RevoluteJoint *joint4 = (b2RevoluteJoint *)World::getWorld()->CreateJoint(&revoluteJointDef4);
	joint4;
	b2GearJointDef gearJointDef2;
	gearJointDef2.bodyA = p3->pBody;
	gearJointDef2.bodyB = p4->pBody;
	gearJointDef2.collideConnected = false;
	gearJointDef2.joint1 = joint3;
	gearJointDef2.joint2 = joint4;

	// screw around with this ratio and sign
	gearJointDef2.ratio = -1.0f;

	World::getWorld()->CreateJoint(&gearJointDef2);


	gObjName;
	float width = 20;
	float height = 10;

	GameObject2D *pGObj = 0;
	GameObject2D *pGObjFirst = BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(p3->posX, p3->posY +p3->origWidth/2, width, height));
	//pGObjFirst->pBody->SetGravityScale(0.0f);
	GameObject2D *pLink = pGObjFirst;
	for (int i = 1; i < 7; i++){

		pGObj = BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(p3->posX + (i*width), p3->posY + p3->origWidth / 2 + 0, width, height));
		//pGObj->pBody->SetGravityScale(0.0f);

		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = pLink->pBody;
		revoluteJointDef.bodyB = pGObj->pBody;
		revoluteJointDef.collideConnected = false;
		revoluteJointDef.localAnchorA.Set(PixelToMeter(width*0.5f), PixelToMeter(0.0f));
		revoluteJointDef.localAnchorB.Set(PixelToMeter(-width*0.5f), PixelToMeter(0.0f));
		revoluteJointDef.userData = 0;

		b2RevoluteJoint *pRJoint = (b2RevoluteJoint*)World::getWorld()->CreateJoint(&revoluteJointDef);
		assert(pRJoint);
		pLink = pGObj;

	}

	for (int i = 1; i < 11; i++){

		pGObj = BlockFactory::Create(GameObjectName::WoodenBlock, ImageName::LongWoodBlock_Healty, Rect(p3->posX + (7 * width) - (i*width),p3->posY- p3->origWidth / 2, width, height));
		//pGObj->pBody->SetGravityScale(0.0f);

		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = pLink->pBody;
		revoluteJointDef.bodyB = pGObj->pBody;
		revoluteJointDef.collideConnected = false;
		revoluteJointDef.localAnchorA.Set(PixelToMeter(width*0.5f), PixelToMeter(0.0f));
		revoluteJointDef.localAnchorB.Set(PixelToMeter(-width*0.5f), PixelToMeter(0.0f));
		revoluteJointDef.userData = 0;

		b2RevoluteJoint *pRJoint = (b2RevoluteJoint*)World::getWorld()->CreateJoint(&revoluteJointDef);
		assert(pRJoint);
		pLink = pGObj;


	}
	//Last one to first one 
	b2RevoluteJointDef revoluteJointDefLast;
	revoluteJointDefLast.bodyA = pLink->pBody;
	revoluteJointDefLast.bodyB = pGObjFirst->pBody;
	revoluteJointDefLast.collideConnected = false;
	revoluteJointDefLast.localAnchorA.Set(PixelToMeter(width*0.5f), PixelToMeter(0.0f));
	revoluteJointDefLast.localAnchorB.Set(PixelToMeter(-width*0.5f), PixelToMeter(0.0f));
	revoluteJointDefLast.userData = 0;

	b2RevoluteJoint *pRJoint = (b2RevoluteJoint*)World::getWorld()->CreateJoint(&revoluteJointDefLast);
	assert(pRJoint);

	return 0;
}