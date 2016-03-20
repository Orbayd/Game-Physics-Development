#include "Ready.h"

#include "RubberBand.h"
#include "GameObjectMan.h"
#include "Bird.h"
#include "TimerMan.h"

#include "JumToSling.h"
#include "Input.h"
Ready::Ready()
{
}

Ready::~Ready()
{
}
Ready *Ready::GetInstance()
{
	static Ready instance;
	return &instance;
}
void Ready::Enter(Bird* pBird)
{
	pBird;
	RubberBand* pBack = (RubberBand*)GameObjectMan::Find(GameObjectName::RubberBandBack);
	RubberBand* pFront = (RubberBand*)GameObjectMan::Find(GameObjectName::RubberBandFront);
	Vect A(pBack->anchorX, pBack->anchorY, 0);
	Vect B(pFront->anchorX, pFront->anchorY, 0);
	Vect C = B - A;
	float len = C.mag();
	C.norm();
	C = C* 0.5 * len;
	C = A + C;

	//firstPos.Set(pBird->posX, pBird->posY);
	//lastPos.Set(C[x], C[y]);
	JumpToSling *pJump = new JumpToSling(pBird, C[x], C[y], pBird->posX, pBird->posY,0);
	TimerMan::AddEvent(0.0f, pJump);
	//pBird->SetPosition(C[x], C[y]);
	//pBird->pBody->SetActive(false);
	TimerMan::CleanObjectEvents(pBird, EventName::JUMP);
}
void Ready::Execute(float totalTime, Bird* pBird)
{

	
	MouseInput(pBird);
	

	totalTime;
	pBird;
}
void Ready::Exit(Bird* pBird)
{
	pBird;
}