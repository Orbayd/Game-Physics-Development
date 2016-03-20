#include <string>
#include "CameraMan.h"
#include "InputMan.h"
#include "Keyboard.h"
#include "DebugOut.h"
#include "GameObject2D.h"
#include "PixelToMeter.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "RubberBand.h"
#include "Level.h"

//Settting Bird
#include "Flying.h"
#include "Bird.h"
enum PositionState
{
	INSIDE,
	OUTSIDE,
	UNKNOWN
};

enum MouseState
{
	RIGHT,
	LEFT,
	NONE
};

enum BirdState2
{
	NORMAL,
	MOVING_RIGHT,
	MOVING_LEFT
};

static BirdState2 bstate = NORMAL;

void KeyboardTest()
{
	Keyboard *key = InputMan::GetKeyboard();

	// Quick and dirty test, if these work the rest do.
	// ---> try a,s,d,<SPACE> keys
	std::string a;
	std::string b;
	std::string c;
	std::string d;

	if (key->GetKeyState(AZUL_KEY::KEY_R))
	{
		Vect A(150.0f, 270.0f, 0.0f);

		GameObject2D * pBird = (GameObject2D *)GameObjectMan::Find(GameObjectName::L1_RedBird);
		if (pBird == 0)
			return;
		a = " R";
		pBird->maxDamage = 0;
		pBird->pBody->SetActive(false);
		pBird->pBody->SetTransform(b2Vec2(PixelToMeter(A[x] - 10),PixelToMeter (A[x] +160)),0.0f);
	}

	if (key->GetKeyState(AZUL_KEY::KEY_S))
	{
		b = " S";
	}

	if (key->GetKeyState(AZUL_KEY::KEY_D))
	{
		c = " D";
	}

	if (key->GetKeyState(AZUL_KEY::KEY_SPACE))
	{
		d = " <SPACE>";
	}

	std::string total = a + b + c + d;
	//printf("Key:%s \n", total.c_str());
	//out("Key:%s \n", total.c_str());
	
}


void MouseTest()
{
	
	//GameObject2D * pBird = (GameObject2D *)GameObjectMan::Find(GameObjectName::L1_RedBird);
	GameObject2D * pBird = (GameObject2D *)GameObjectMan::getActiveBird();
	if (pBird == 0)
		return;
	RubberBand * pRubberBandFront = (RubberBand *)GameObjectMan::Find(GameObjectName::RubberBandFront); pRubberBandFront;
	if (pRubberBandFront == 0)
		return;
	 RubberBand * pRubberBandBack = (RubberBand *)GameObjectMan::Find(GameObjectName::RubberBandBack); pRubberBandBack;
	if (pRubberBandBack == 0)
		return;
	Mouse *mouse = InputMan::GetMouse();

	MouseState mstate = NONE; mstate;
	PositionState pstate = UNKNOWN; pstate;

	//bstate;
	//// Quick and dirty test, if these work the rest do.
	//// --> try move the mouse inside the window, click right, click left
	//std::string a;
	//std::string b;
	Vect MousePos(0.0f, 0.0f, 0.0f);
	/*float xPos;
	float yPos;*/

	//// get mouse position
	mouse->GetCursor(MousePos[x], MousePos[y]);

	Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
	pCam->CorrectForOrigin(MousePos[x], MousePos[y]);

	//// inside bird?
	b2Body *pBody = pBird->pBody;
	if (pBody == 0)
		return;

	b2Fixture *pFix = pBody->GetFixtureList();
	assert(pFix->GetNext() == 0);

	if (pFix->TestPoint(b2Vec2(PixelToMeter(MousePos[x]), PixelToMeter(MousePos[y]))))
	{
		pstate = INSIDE;
		//out("mouse : inside\n");
	}
	else
	{
		pstate = OUTSIDE;
		//out("mouse: (%d,%d) \n", MousePos[x], (MousePos[y]);
		//out("outside\n");
	}
	
	mstate = NONE;
	if (mouse->GetKeyState(AZUL_MOUSE::BUTTON_RIGHT))
	{
		mstate = RIGHT;
	}

	if (mouse->GetKeyState(AZUL_MOUSE::BUTTON_LEFT))
	{
		mstate = LEFT;
	}


	if (mstate == LEFT && pstate == INSIDE)
	{
		pBody->SetActive(false);
		//pBody->SetActive(true);
		
		bstate = MOVING_LEFT;
		
	}

	Vect RubberFrontFixPos(pRubberBandFront->anchorX, pRubberBandFront->anchorY, 0);
	Vect RubberBackFixPos(pRubberBandBack->anchorX, pRubberBandBack->anchorY, 0);
	
	Vect currentPos( MousePos[x], MousePos[y], 0);
	Vect vectA = RubberFrontFixPos - currentPos;

	Vect VectB = RubberBackFixPos - currentPos;
	
	// Anchor and max


	float maxLength = 70.0f;
	if (vectA.mag() > maxLength)
	{
		// Adjust B to maxLength
		vectA.norm();
		vectA *= maxLength;// *Level::getScale();
		currentPos = RubberFrontFixPos - vectA;

		VectB.norm();
		VectB *= maxLength;//* Level::getScale();


	}
	
	if (bstate == MOVING_LEFT)
	{

		if (mstate == LEFT)
		{
			 pBody->SetActive(false);
			//pBody->SetActive(true);
		}
		if (mouse->IsReleased(AZUL_MOUSE::BUTTON_LEFT))
		{
			
			//pBird->pBody->SetGravityScale(1.0f);
			
			float speed = vectA.mag();
			speed *= Level::getScale();
			b2Vec2 angle(vectA[x], vectA[y]);
			
			angle.Normalize();
			b2Vec2 vel =  speed * angle;
			
			out("Velocity:(%f,%f) \n", vel.x, vel.y);
			out("Speed:(%f) \n", speed);
			pBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			pBody->SetActive(true);
			pBody->ApplyLinearImpulse(vel, pBody->GetWorldCenter(), true);

			
		
			bstate = NORMAL;

			Vect verts[4];
			verts[0] = Vect(0, 0, 0);
			verts[1] = Vect(0, 0, 0);
			verts[2] = Vect(0, 0, 0);
			verts[3] = Vect(0, 0, 0);
			GraphicsObject_Quad*pGraphics_Quad_Back = (GraphicsObject_Quad*)pRubberBandFront->getGraphicsObject();
			pGraphics_Quad_Back->setVects(verts);

			GraphicsObject_Quad*pGraphics_Quad_Front = (GraphicsObject_Quad*)pRubberBandBack->getGraphicsObject();
			pGraphics_Quad_Front->setVects(verts);

			if (vel.Length()>10.0)
			{
				Bird* p = (Bird*)pBird;
				p->ChangeState(Fly::GetInstance());
				
			}

		}
		else
		{
			Vect Perp(-vectA[y], vectA[x], 0);
			Perp.norm();
			Perp *= 5.0f;//::getScale() ;

			Vect verts[4];
			verts[0] = RubberFrontFixPos - Perp;
			verts[1] = currentPos - Perp;
			verts[2] = currentPos + Perp;
			verts[3] = RubberFrontFixPos + Perp;
			GraphicsObject_Quad*pGraphics_Quad_Front = (GraphicsObject_Quad*)pRubberBandFront->getGraphicsObject();
			pGraphics_Quad_Front->setVects(verts);



			Vect PerpFront(-VectB[y], VectB[x], 0);
			PerpFront.norm();
			PerpFront *= 5.0f;//* Level::getScale();

			Vect vertsFront[4];
			vertsFront[0] = RubberBackFixPos - PerpFront;
			vertsFront[1] = currentPos - PerpFront;
			vertsFront[2] = currentPos + PerpFront;
			vertsFront[3] = RubberBackFixPos + PerpFront;
			GraphicsObject_Quad*pGraphics_Quad_Back = (GraphicsObject_Quad*)pRubberBandBack->getGraphicsObject();
			pGraphics_Quad_Back->setVects(vertsFront);

			//b2Vec2 line(vectA[x], vectA[y]);
			//line.Normalize();
			pBody->SetTransform(b2Vec2(PixelToMeter(currentPos[x]), PixelToMeter(currentPos[y])), 0);
			//pBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			//pBody->ApplyLinearImpulse(line, pBody->GetWorldCenter(), true);



		}
	}


	//Update Rubber band 


}

bool isInside(GameObject2D *pGobj,float xPos,float yPos)
{
	b2Body *pBody = pGobj->pBody;

	b2Fixture *pFix = pBody->GetFixtureList();
	assert(pFix->GetNext() == 0);

	if (pFix->TestPoint(b2Vec2(PixelToMeter(xPos), PixelToMeter(yPos))))
	{
		return true;
	}
	else
	{
		return false;
//		out("mouse: (%d,%d) \n", (int)xPos, (int)yPos);
	}
}




