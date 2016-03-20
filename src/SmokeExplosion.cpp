#include <assert.h>

#include "SmokeExplosion.h"
#include "PixelToMeter.h"
#include "World.h"

#include "GameObjectMan.h"
#include "AzulHelper.h"
#include "Simulation.h"
#include "ImageMan.h"
SmokeExplosion::SmokeExplosion(GameObjectName::Name name, GraphicsObject_Sprite *pSprite, GameSortBucket *pSort)
	:Particle(name, pSprite, pSort)
{
	this->maxLifeTime = 0.2f;
	this->animationTime = maxLifeTime * 0.20f;
}

SmokeExplosion *SmokeExplosion::Create(GameObjectName::Name gObjName, ImageName::Name imageName, Rect rect, GameSortBucket *pSort)
{
	assert(pSort);

	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(imageName, rect);
	assert(pSprite);

	SmokeExplosion *pParticle = new SmokeExplosion(gObjName, pSprite, pSort);
	assert(pParticle);

	return pParticle;
}

void SmokeExplosion::CreateBody(b2Vec2 center, float scale, float _angle, b2Vec2 linVel, float angleVel)
{
	
	center; scale; _angle; linVel; angleVel; angleVel;
	
	

}

void SmokeExplosion::WorldUpdate(float currentTime)
{
	currentTime;
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = Scale * Rot * Trans;

	float timeInSec = Simulation::Instance()->getTimeStep();
	this->lifeTime += timeInSec;

	//// add schrink
	

	if (this->lifeTime >= animationTime)
	{
		//protection
			ImageName::Name iNmae = ((GraphicsObject_Sprite*)this->getGraphicsObject())->pImage->name;
			if (iName != ImageName::SmokeExplosion_4 + 1)//Protection 
			{


				int nextImage  =  (static_cast<int>(iNmae + 1));
				Image *img = ImageMan::find((ImageName::Name)nextImage);

				this->getGraphicsObject()->SetImage((ImageName::Name)nextImage);
				float ratioWidth = 1 + (img->imageRect.width - this->origWidth) / (this->origWidth);
				float ratioHeight = 1 + (img->imageRect.height - this->origHeight) / (this->origHeight);
				this->scaleX = ratioWidth;
				this->scaleY = ratioHeight;
				lifeTime = 0;
				
			}
			this->maxLifeTime -= animationTime;
	}
	if (maxLifeTime <= 0.0f)
	{
		this->deleteMe = true;
		GameObjectMan::AddToDeleteList(this);
	}
	
	



}
