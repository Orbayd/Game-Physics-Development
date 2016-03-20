#include <assert.h>

#include "DebugOut.h"
#include "MathEngine.h"
#include "GameObject.h"

#include "GameObjectMan.h"
#include "GameObject2D.h"
#include "GraphicsObject_Sprite.h"
#include "GraphicsObject_Circle.h"
#include "AzulHelper.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "PixelToMeter.h"
#include "Vect2D.h"
#include "Color.h"
#include "Box2D.h"
#include "World.h"

#include "SoundMan.h"
// HACK
//extern b2World *pB2World;

GameObject2D::GameObject2D(GameObjectName::Name _name)
{
	this->damage = 0.0f;
	this->pendingDamage = 0.0f;
	this->maxDamage = 1.0f;

	this->drawSprite = true;
	this->drawDebug = true;

	this->name = _name;
	this->angle = 0.0f;
	this->posX = 0.0f;
	this->posY = 0.0f;
	this->scaleX = 1.0f;
	this->scaleY = 1.0f;
	
	this->pGameSprite = 0;

	this->origHeight = 0;
	this->origWidth = 0;

	this->pBody = 0;
	this->debugColor = Color::Type::Yellow;
}


GameObject2D::GameObject2D(GameObjectName::Name _name, GraphicsObject_Quad  *_pGraphicsObject)
{
	this->damage = 0.0f;
	this->pendingDamage = 0.0f;
	this->maxDamage = 1.0f;

	this->drawSprite = true;
	this->drawDebug = false;

	this->name = _name;
	this->angle = 0.0f;
	this->posX = 0.0f;
	this->posY = 0.0f;
	this->scaleX = 1.0f;
	this->scaleY = 1.0f;

	this->pGameSprite = _pGraphicsObject;

	this->origHeight = 0.0f;
	this->origWidth = 0.0f;

	this->pBody = 0;
	this->debugColor = Color::Type::Yellow;

	assert(pGameSprite != 0);
}

GameObject2D::GameObject2D(GameObjectName::Name _name, GraphicsObject_Sprite  *_pGraphicsObject)
{
	
	this->iName = static_cast<ImageName::Name>(static_cast<int> (_pGraphicsObject->pImage->name) );
	
	this->damage = 0.0f;
	this->pendingDamage = 0.0f;
	this->maxDamage = 1.0f;
	
	this->drawSprite = true;
	this->drawDebug = true;

	this->name = _name;
	this->angle = 0.0f;
	this->posX = _pGraphicsObject->origPosX;
	this->posY = _pGraphicsObject->origPosY;
	this->scaleX = 1.0f;
	this->scaleY = 1.0f;

	this->pGameSprite = _pGraphicsObject;

	this->origHeight = _pGraphicsObject->origHeight;
	this->origWidth = _pGraphicsObject->origWidth;

	this->pBody = 0;
	this->debugColor = Color::Type::Yellow;

	assert(pGameSprite != 0);
}


GameObject2D::GameObject2D(GameObjectName::Name _name, GraphicsObject_Circle  *_pGraphicsObject)
{
	this->damage = 0.0f;
	this->pendingDamage = 0.0f;
	this->maxDamage = 1.0f;

	this->drawSprite = true;
	this->drawDebug = false;

	this->name = _name;
	this->angle = 0.0f;
	this->posX = _pGraphicsObject->origPosX;
	this->posY = _pGraphicsObject->origPosY;
	this->scaleX = 1.0f;
	this->scaleY = 1.0f;

	this->pGameSprite = _pGraphicsObject;

	assert(_pGraphicsObject->origHeight == _pGraphicsObject->origWidth);
	this->origHeight = _pGraphicsObject->origHeight;
	this->origWidth = _pGraphicsObject->origWidth;

	this->pBody = 0;
	this->debugColor = Color::Type::Yellow;

	assert(pGameSprite != 0);
}

bool GameObject2D::HasBody()
{
	return (pBody != 0);
}
EnumBase GameObject2D::getName()
{
	return GameObjectName((EnumBase::Name)this->name);
}
bool GameObject2D::drawEnabled()
{
	return this->drawSprite;
}

GraphicsObject *GameObject2D::getGraphicsObject()
{
	return this->pGameSprite;
};

GameObject2D::~GameObject2D()
{
	if (this->HasBody()){
		World::getWorld()->DestroyBody(this->pBody);
	}
	//out("Deleted: %d", this->name);
	delete this->pGameSprite;
	
}

void GameObject2D::PhysicsUpdate(b2Vec2 posInMeters, float angleInRadians)
{
	// updates position and angle from physics update
	this->posX = MeterToPixel(posInMeters.x);
	this->posY = MeterToPixel(posInMeters.y);
	this->angle = angleInRadians;
}

void GameObject2D::WorldUpdate(float currentTime)
{
	AZUL_UNUSED_FLOAT(currentTime);

	// Goal: update the world matrix
	Matrix Scale(MatrixScaleType::SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix Rot(RotType::ROT_Z, this->angle);
	Matrix Trans(MatrixTransType::TRANS, this->posX, this->posY, 0.0f);

	*this->pWorld = Scale * Rot * Trans;

}

void GameObject2D::SetPosition(const float _x, const float _y)
{
	if (HasBody())
	{
		this->pBody->SetTransform(b2Vec2(PixelToMeter(_x), PixelToMeter(_y)),0.0f);
	}


}
void GameObject2D::AddDamage(float normalImpulse)
{
	if (this->pBody->GetType() != b2_staticBody)
	{
		this->damage += normalImpulse;
		this->pendingDamage += normalImpulse;
		//out("(%x)Damage:%f\n", this->getName(), this->damage);
	}
}

float GameObject2D::PendingLifeLeft()
{
	return this->maxDamage - this->pendingDamage;
}
