#include <assert.h>
#include "CameraMan.h"


void CameraMan::SetCurrentCamera(Camera *camera, Camera::Type type)
{
	assert( camera != 0 );
	CameraMan *pCamMan = CameraMan::privInstance();
	switch (type)
	{
	case Camera::Type::PERSPECTIVE_3D:
		assert( camera->getType() == Camera::Type::PERSPECTIVE_3D );
		pCamMan->pCamPerspective = camera;
		break;

	case Camera::Type::ORTHOGRAPHIC_2D:
		assert( camera->getType() == Camera::Type::ORTHOGRAPHIC_2D );
		pCamMan->pCamOrthographic = camera;
		break;

	default:
		assert(false);
		break;
	}
	
}

Camera * CameraMan::GetCurrent(Camera::Type type)
{
	Camera *pCam = 0;
	switch (type)
	{
	case Camera::Type::PERSPECTIVE_3D:
		pCam = CameraMan::privInstance()->pCamPerspective;
		break;

	case Camera::Type::ORTHOGRAPHIC_2D:
		pCam = CameraMan::privInstance()->pCamOrthographic;
		break;

	default:
		assert(false);
		break;
	}
	
	assert( pCam != 0 );
	return pCam;
}

CameraMan *CameraMan::privInstance()
{
	static CameraMan camMan;
	return &camMan;
}

CameraMan::CameraMan()
{
	this->pCamPerspective = 0;
	this->pCamOrthographic = 0;
}

CameraMan::~CameraMan()
{
	delete this->pCamPerspective;
	delete this->pCamOrthographic;
}