#ifndef CAMERA_MAN_H
#define CAMERA_MAN_H

#include "Camera.h"

class CameraMan
{
public:
	static Camera *GetCurrent(Camera::Type type);
	static void SetCurrentCamera(Camera *camera, Camera::Type type);

	~CameraMan();

private:
	static CameraMan *privInstance();
	CameraMan();
	

	// Data
	Camera *pCamOrthographic;
	Camera *pCamPerspective;
};

#endif