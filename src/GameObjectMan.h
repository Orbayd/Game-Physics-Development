#ifndef GAME_OBJECT_MAN_H
#define GAME_OBJECT_MAN_H

#include "GameObject.h"
#include "GameSortBucket.h"
#include "PCSTree.h"
class GameObject2D; //forward Decleration
class GameObjectDeleteLink
{
public:
	GameObjectDeleteLink(GameObject *pObj)
		:p(pObj), next(0)
	{

	}

	GameObjectDeleteLink *next;
	GameObject *p;
};

// Singleton
class GameObjectMan
{
public:

	static void Add(GameSortBucket *pGameSort, GameObject *pObjParent = 0);
	static void Add( GameObject *pObj, GameSortBucket *pGameSort );
	static void Draw( void );
	static void Update( float currentTime );

	static void Delete(GameObject *pObj);
	static GameObject *Find(GameObjectName::Name name);
	
	static void AddToDeleteList(GameObject *pObj);
	static void DeletePending();
	

	static void Clear();
	static void CreateSorting();
	static GameObject2D* getActiveBird();
	static void setActiveBird(GameObject2D* pBird);
private:
	GameObjectMan();


	void privDrawDebug(PCSNode *pNode);
	void privDrawSprite(PCSNode *pNode);
	void privDraw(GameObjectMan *pGOM, PCSNode *pNode);
	void privUpdate(GameObjectMan *pGOM, PCSNode *pNode, float currentTime);
	void privFind(GameObject **pObj, GameObjectMan *pGOM, PCSNode *pNode, GameObjectName::Name name);
	
	void privClear(GameObjectMan *pGOM, GameObject* pObj);

	static GameObjectMan *privGetInstance();
	PCSTree *pRootTree;

	GameObjectDeleteLink *pDeleteLink;
	GameObject2D * activeBird;
};

#endif