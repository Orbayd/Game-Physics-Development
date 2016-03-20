#include "SlingShotFactory.h"
#include "GraphicsObject.h"
#include "GameObjectMan.h"
#include "GameSortBucket.h"
#include "Level.h"
#include "RubberBand.h"
#include "Seat.h"
#include "PixelToMeter.h"
#include "World.h"
void  SlingShotFactory::Create(Vect &_pivot)
{
	Vect Pivot = _pivot;
		
	float scale = Level::getScale();
	 
	 GraphicsObject_Sprite *pGraphics_Sprite;
	 pGraphics_Sprite = new GraphicsObject_Sprite(ImageName::SlingshotFront, Rect(Pivot[x], Pivot[y], 40 * scale, 200 * scale));
	 GameObject2D * pSlingFront = new GameObject2D(GameObjectName::SlingShootFront, pGraphics_Sprite);
	 pSlingFront->scaleX = pSlingFront->scaleY ;
	 GameObject *pObj = GameObjectMan::Find(GameObjectName::SlingShootFront_Sort);
	 assert(pObj);
	 GameSortBucket *pBucket = (GameSortBucket *)pObj;
	 GameObjectMan::Add(pSlingFront, pBucket);
	

	 pGraphics_Sprite = new GraphicsObject_Sprite(ImageName::SlingshotBack, Rect(Pivot[x] - (23 * scale), Pivot[y] + (45*scale), 40 * scale, 125 * scale));
	 GameObject2D * pSlingBack = new GameObject2D(GameObjectName::SlingShootBack, pGraphics_Sprite);
	 pSlingBack->scaleX = pSlingBack->scaleY ;
	 pObj = GameObjectMan::Find(GameObjectName::SlingShootBack_Sort);
	 assert(pObj);
	 pBucket = (GameSortBucket *)pObj;
	GameObjectMan::Add(pSlingBack, pBucket);
	
	CreateBody(pSlingFront);
	
	CreateRubberBand(_pivot);
	//CreateSeat(_pivot);
}

void SlingShotFactory::CreateRubberBand(Vect &pivot)
{

	//RubberBand
	Vect2D vertList[4];

	// Counter clock wise rotation
	vertList[0].x = 0;
	vertList[0].y = 0;

	vertList[1].x = 0;
	vertList[1].y = 0;

	vertList[2].x = 0;
	vertList[2].y = 0;

	vertList[3].x = 0;
	vertList[3].y = 0;

	GameObject *pObj = GameObjectMan::Find(GameObjectName::RubberBandBack_Sort);
	assert(pObj);
	GameSortBucket *pSortBucket = (GameSortBucket *)pObj;
	GraphicsObject_Quad*	pGraphics_Quad_Back = new GraphicsObject_Quad(ImageName::RubberBand, vertList);
	
	RubberBand * pRubberBack = new RubberBand(GameObjectName::RubberBandBack, pGraphics_Quad_Back, pSortBucket);
	pRubberBack->SetAnchorPoint(pivot[x]+(5*Level::getScale()),pivot[y]+(70*Level::getScale()));
	//GameObjectMan::Add(pRubberBack, pSortBucket);


	pObj = GameObjectMan::Find(GameObjectName::RubberBandFront_Sort);
	assert(pObj);
	pSortBucket = (GameSortBucket *)pObj;
	GraphicsObject_Quad *pGraphics_Quad_Front = new GraphicsObject_Quad(ImageName::RubberBand, vertList);
	RubberBand * pRubberFront = new RubberBand(GameObjectName::RubberBandFront, pGraphics_Quad_Front, pSortBucket);
	pRubberFront->SetAnchorPoint(pivot[x] - (25 * Level::getScale()), pivot[y] + (70*Level::getScale()));
	//GameObjectMan::Add(pRubberFront, pSortBucket);

}

void SlingShotFactory::CreateBody(GameObject2D * pSlingShot)
{

	// Body Def
	b2BodyDef BodyDef;
	BodyDef.type = b2BodyType::b2_staticBody;
	BodyDef.position.Set(PixelToMeter(pSlingShot->posX), PixelToMeter(pSlingShot->posY));
	BodyDef.angle = pSlingShot->angle;

	// Shape
	b2PolygonShape shape;
	shape.SetAsBox(PixelToMeter(pSlingShot->origWidth * 0.20f), PixelToMeter(pSlingShot->origHeight * 0.20f), b2Vec2(-0.2f*Level::getScale(), -1.0f*Level::getScale()), 0);

	// Body
	b2Body *pBlockBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &shape;
	FixtureDef.density = 10.0f;
	FixtureDef.friction = 0.3f;
	FixtureDef.restitution = 0.5f;
	FixtureDef.userData = pSlingShot;

	pBlockBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pBlockBody->SetUserData(pSlingShot);

	// GameObject points to Body
	pSlingShot->pBody = pBlockBody;



}

void SlingShotFactory::CreateSeat(Vect &pivot)
{
	pivot;
	GameObject *pObj = GameObjectMan::Find(GameObjectName::RubberBandBack_Sort);
	assert(pObj);
	GameSortBucket *pSortBucket = (GameSortBucket *)pObj;
	

	RubberBand* pBack = (RubberBand*)GameObjectMan::Find(GameObjectName::RubberBandBack);
	RubberBand* pFront = (RubberBand*)GameObjectMan::Find(GameObjectName::RubberBandFront);
	Vect A(pBack->anchorX, pBack->anchorY, 0);
	Vect B(pFront->anchorX, pFront->anchorY, 0);
	Vect C = B - A;
	float len = C.mag();
	C.norm();
	C = C* 0.5 * len;
	C = A + C;
	
	GraphicsObject_Sprite *pSprite = new GraphicsObject_Sprite(ImageName::Bang, Rect(C[x],C[y],15,15));
	Seat *pSeat = new Seat(GameObjectName::SlingShootSeat, pSprite, pSortBucket); pSeat;

	//CreateBody


	// Body Def
	b2BodyDef BodyDef;
	BodyDef.type = b2BodyType::b2_staticBody;
	BodyDef.position.Set(PixelToMeter(pSeat->posX), PixelToMeter(pSeat->posY));
	BodyDef.angle = pSeat->angle;

	// Shape
	b2PolygonShape shape;
	shape.SetAsBox(PixelToMeter(pSeat->origWidth * 0.5f), PixelToMeter(pSeat->origHeight * 0.5f), b2Vec2(0.0f, 0.0f), 0);

	// Body
	b2Body *pBlockBody = World::getWorld()->CreateBody(&BodyDef);

	// Fixture
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &shape;
	FixtureDef.density = 10.0f;
	FixtureDef.friction = 0.3f;
	FixtureDef.restitution = 0.5f;
	FixtureDef.userData = pSeat;

	pBlockBody->CreateFixture(&FixtureDef);

	// Body points to GameObject
	pBlockBody->SetUserData(pSeat);

	// GameObject points to Body
	pSeat->pBody = pBlockBody;
}