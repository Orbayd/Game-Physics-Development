#ifndef CAMERA_DIRECTOR_H
#define CAMERA_DIRECTOR_H
class Bird;
class CameraDirector
{
public:
	static CameraDirector* getInstance();
	static void Update(Bird *pBird);
	~CameraDirector();
private:
	CameraDirector();
};




#endif