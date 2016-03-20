#ifndef SMOKE_MANAGER_H
#define SMOKE_MANAGER_H
#include "Vect.h"
class GameSortBucket;

class SmokeManager
{
public:
	
	~SmokeManager();
	static void CreateSmoke(float PosX, float PosY);
	static void Update(float totalTime);
	static void ClearBucket();
private:
	static SmokeManager* getInstance();
	static bool CheckDistance();
	static void SwitchBuckets();
	
	SmokeManager();
	GameSortBucket * active;
	GameSortBucket * passive;
	Vect SmokePos;

};




#endif