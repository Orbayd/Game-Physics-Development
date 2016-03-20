#ifndef SMOKE_MANAGER_H
#define SMOKE_MANAGER_H
#include "Vect.h"
class TrailEmitter;
class GameSortBucket;
class Bird;
class SmokeManager
{
public:
	
	~SmokeManager();
	static void CreateSmoke(float PosX, float PosY, Bird *pBird);
	static void CreateSmokeP(float PosX, float PosY, Bird *pBird);
	static void Update(float totalTime, Bird *pBird);
	static void UpdateP(float totalTime, Bird *pBird);
	static void ClearBucket();
	static void SwitchBuckets();
	static void AddSmoke(Bird *pBird);
private:
	static SmokeManager* getInstance();
	static bool CheckDistance(Bird *pBird);
	
	
	SmokeManager();
	GameSortBucket * active;
	GameSortBucket * passive;
	GameSortBucket * activeParticleSmoke;
	GameSortBucket * passiveParticleSmoke;
	
	Vect SmokePos;

};




#endif