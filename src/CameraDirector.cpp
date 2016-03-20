#include "CameraDirector.h"
#include "CameraMan.h"
#include "GameObjectMan.h"
#include "Bird.h"
#include "GameObjectMan.h"
#include "Ready.h"
#include "SmokeTrailMan.h"
#include "TimerMan.h"
CameraDirector::CameraDirector()
{
}

CameraDirector::~CameraDirector()
{
}
CameraDirector * CameraDirector::getInstance()
{
	static CameraDirector instance;
	return &instance;
}
void CameraDirector::Update(Bird *pBird)
{
	Camera *pCam = CameraMan::GetCurrent(Camera::Type::ORTHOGRAPHIC_2D);
	Vect initalpCamPos;
	Vect pos;
	Vect lookAt;
	Vect initalLookAt;
	pCam->getPos(initalpCamPos);
	pCam->getLookAt(initalLookAt);
	if (pBird->posX >= 100 - 1280 * 0.5f && pBird->posX < 600 + 1280 + 1280 * 0.5f && pBird->posY < 1366 * 0.5f + 800)
	{
		pCam->TargetWorldScreen(pos, lookAt, pBird->posX, pBird->posY);
		Vect up;
		pCam->getUp(up);
		pCam->setOrientAndPosition(up, lookAt, pos);
		//out("Bird Position %f, %f \n", pBird->posX, pBird->posY);
		//out("Camera Position %f, %f \n", pos[x], pos[y]);
	}
	else{
		Vect up;
		pCam->getUp(up);
		SmokeManager::SwitchBuckets();
		TimerMan::CleanObjectEvents(pBird);
		Bird* pSibling = (Bird*)pBird->getSibling();
		if (pSibling != 0)
		{
			GameObjectMan::setActiveBird(pSibling);
			pSibling->ChangeState(Ready::GetInstance());

			pCam->TargetWorldScreen(pos, lookAt, pSibling->posX, pSibling->posY);
			pCam->setOrientAndPosition(up, lookAt, pos);
			GameObjectMan::AddToDeleteList(pBird);
		}
		else{
		
			pCam->setOrientAndPosition(up, initalLookAt, initalpCamPos);
			pCam->updateCamera();
		}
	}
}