#include <assert.h>

#include "GameObject.h"
#include "GameObject2D.h"
#include "GameObjectMan.h"
#include "PixelToMeter.h"
#include "DebugOut.h"
#include "Vect2D.h"
#include "GraphicsObject_Circle.h"
#include "GraphicsObject_Tri.h"
#include "TimerMan.h"

void GameObjectMan::Add(GameObject *pObj, GameSortBucket *pGameSort)
{
	assert(pObj != 0);
	assert(pGameSort != 0);

	// Get singleton
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();

	// insert object to root
	pGOM->pRootTree->insert(pObj, pGameSort);
}


void GameObjectMan::Add(GameSortBucket *pGameSort, GameObject *pObjParent)
{
	assert(pGameSort != 0);
	PCSNode *pObj;

	// Get singleton
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();

	// if its zero, root is parent
	if (pObjParent == 0)
	{
		// Get root node
		pObj = pGOM->pRootTree->getRoot();
	}
	else
	{
		pObj = pObjParent;
	}

	// insert object to root
	pGOM->pRootTree->insert(pGameSort, pObj);
}

void  GameObjectMan::AddToDeleteList(GameObject *pObj)
{
	assert(pObj != 0);
	// Get singleton
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	pObj->deleteMe = true;
	GameObjectDeleteLink *pDel = new GameObjectDeleteLink(pObj);

	// Add to front
	pDel->next = pGOM->pDeleteLink;
	pGOM->pDeleteLink = pDel;
}


void GameObjectMan::Delete(GameObject *pObj)
{
	assert(pObj);

	// Get singleton
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();

	pObj->deleteMe = true;
	pGOM->pRootTree->remove(pObj);

	// delete this node game object
	delete pObj;
}

GameObject *GameObjectMan::Find(GameObjectName::Name name)
{
	// Get singleton
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert(pGOM);

	GameObject *pObj = 0;
	pGOM->privFind(&pObj, pGOM, pGOM->pRootTree->getRoot(), name);

	return pObj;
}


void GameObjectMan::privFind(GameObject **pObj, GameObjectMan *pGOM, PCSNode *pNode, GameObjectName::Name name)
{
	// Update the game object
	GameObject *pGameObj = (GameObject2D *)pNode;


	if (pGameObj->getName().value == name )
	{
		*pObj = pGameObj;
		return;
	}

	{
		// iterate through all of the active children 
		if (pNode->getChild() != 0)
		{
			PCSNode *pChild = pNode->getChild();
			// make sure that allocation is not a child node 
			while (pChild != 0)
			{
				pGOM->privFind(pObj, pGOM, pChild, name);
				// goto next sibling
				pChild = pChild->getSibling();
			}
		}
		else
		{
			// bye bye exit condition
		}
	}
}


void  GameObjectMan::DeletePending()
{
	// Get singleton
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();

	GameObjectDeleteLink *pDel = pGOM->pDeleteLink;
	while (pDel)
	{
		GameObjectDeleteLink *ptmp = pDel->next;
		
		pGOM->pRootTree->remove(pDel->p);
		
		// delete this node game object
		delete pDel->p;
	
		// detete the container for the delete list
		delete pDel;

		pGOM->pDeleteLink = ptmp;

		pDel = ptmp;
	}
}

void GameObjectMan::Update(float currentTime)
{
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert(pGOM);

	PCSNode *pRootNode = pGOM->pRootTree->getRoot();
	assert(pRootNode);

	// update
	pGOM->privUpdate(pGOM, pRootNode, currentTime);
}


void GameObjectMan::privUpdate(GameObjectMan *pGOM, PCSNode *pNode, float currentTime)
{
	// Update the game object
	GameObject *pGameObj = (GameObject *)pNode;
	pGameObj->Update(currentTime);

	// iterate through all of the active children 
	if (pNode->getChild() != 0)
	{
		PCSNode *pChild = pNode->getChild();
		// make sure that allocation is not a child node 
		while (pChild != 0)
		{
			pGOM->privUpdate(pGOM, pChild, currentTime);
			// goto next sibling
			pChild = pChild->getSibling();
		}
	}
	else
	{
		// bye bye exit condition
	}
}
void GameObjectMan::Clear()
{
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert(pGOM);

	GameObject *pRootNode = GameObjectMan::Find(GameObjectName::Root);

	GameObject *pGObj = (GameObject *)pRootNode->getChild();
	assert(pRootNode);
	if (pGObj!=0)
		pGOM->privClear(pGOM, pGObj);
}

void GameObjectMan::privClear(GameObjectMan *pGOM, GameObject* pObj)
{
	assert(pObj);
	if (pObj != pGOM->pRootTree->getRoot())
	{

		GameObject *pChild = (GameObject *)pObj->getChild();
		GameObject *pSibling = (GameObject *)pObj->getSibling();
		GameObject *pParent = (GameObject *)pObj->getParent();
		if (pChild != 0)
			privClear(pGOM, pChild);
		else
		{

			pGOM->pRootTree->remove(pObj);
			pObj->deleteMe = true;
			TimerMan::CleanObjectEvents((GameObject2D*)pObj);
			delete pObj;
			if (pSibling != 0)
			{
				privClear(pGOM, pSibling);
			}
			else if (pParent != 0)
			{

				privClear(pGOM, pParent);
			}
		}

	}

}
void GameObjectMan::Draw()
{
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert(pGOM);

	PCSNode *pRootNode = pGOM->pRootTree->getRoot();
	assert(pRootNode);

	// Draw eveything in depth first order
	pGOM->privDraw(pGOM, pRootNode);
}

void GameObjectMan::privDraw(GameObjectMan *pGOM, PCSNode *pNode) 
{
	assert(pGOM);
	assert(pNode);

	// draw sprite
	pGOM->privDrawSprite(pNode);

	// draw debug volumes
	pGOM->privDrawDebug(pNode);


	// iterate through all of the active children 
	if (pNode->getChild() != 0)
	{
		PCSNode *pChild = pNode->getChild();
		// make sure that allocation is not a child node 
		while (pChild != 0)
		{
			pGOM->privDraw(pGOM, pChild);
			// goto next sibling
			pChild = pChild->getSibling();
		}
	}
	else
	{
		// bye bye exit condition
	}
}


GameObjectMan::GameObjectMan()
{
	this->pRootTree = new PCSTree();
	assert(this->pRootTree);

	//PCSNode *pRootNode = new PCSNode("GameObject_Root");
	PCSNode *pRootNode = new GameObject2D(GameObjectName::Name::Root);
	assert(pRootNode);

	// Set it to be root
	pRootTree->insert(pRootNode, 0);

	this->activeBird = 0;
}


GameObjectMan * GameObjectMan::privGetInstance(void)
{
	// This is where its actually stored (BSS section)
	static GameObjectMan gom;

	return &gom;
}


void GameObjectMan::privDrawSprite(PCSNode *pNode)
{
	// walk through all the nodes
	GameObject *pGameObj = 0;
	GraphicsObject *pGraphicsObj = 0;

	pGameObj = (GameObject *)pNode;
	pGraphicsObj = pGameObj->getGraphicsObject();
	if (pGraphicsObj && pGameObj->drawEnabled())
	{
		pGraphicsObj->Render();
	}
}

void GameObjectMan::privDrawDebug(PCSNode *pNode)
{
	assert(pNode);
	GameObject * pGobj = (GameObject *)pNode;
	if (pGobj->HasBody()){
		// If it exists, draw collision object
		GameObject2D *pGameObj2D = (GameObject2D *)pNode;



		b2Body *pBody = pGameObj2D->pBody;

		if (pBody != 0 && pGameObj2D->drawDebug)
		{
			// -----------------------------------------------------------------
			// Create the matrix
			// -----------------------------------------------------------------
			b2Transform mtmp = pBody->GetTransform();
			Matrix Trans(TRANS, (mtmp.p.x), (mtmp.p.y), 0.0f);
			Matrix Rot(IDENTITY);
			Matrix M;

			Rot[m0] = mtmp.q.c;
			Rot[m1] = mtmp.q.s;
			Rot[m2] = 0.0f;
			Rot[m3] = 0.0f;

			Rot[m4] = -mtmp.q.s;
			Rot[m5] = mtmp.q.c;
			Rot[m6] = 0.0f;
			Rot[m7] = 0.0f;

			M = Rot * Trans;

			b2Fixture *pFix = pBody->GetFixtureList();

			while (pFix != 0)
			{
				switch (pFix->GetType())
				{
				case b2Shape::e_polygon:
				{
					// -----------------------------------------------------------------------
					// Initialize list to the first point, so it can handle 
					// 3,4,5,6,7,8 point polygon easily
					//------------------------------------------------------------------------
					Vect2D vList[8];

					b2PolygonShape* s = (b2PolygonShape*)pFix->GetShape();

					Vect vin(s->m_vertices[0].x, s->m_vertices[0].y, 0.0f);
					Vect vout = vin * M;
					vList[0].x = MeterToPixel(vout[x]);
					vList[0].y = MeterToPixel(vout[y]);

					for (int i = 0; i < 8; i++)
					{
						vList[i] = vList[0];
					}

					// -----------------------------------------------------------------------
					// Now do the rest of points
					//------------------------------------------------------------------------

					for (int i = 1; i < s->m_count; ++i)
					{
						Vect vin(s->m_vertices[i].x, s->m_vertices[i].y, 0.0f);

						Vect vout = vin * M;

						vList[i].x = MeterToPixel(vout[x]);
						vList[i].y = MeterToPixel(vout[y]);
					}

					GraphicsObject_Tri *pSprite = new GraphicsObject_Tri(vList);
					pSprite->debugColor = pGameObj2D->debugColor;
					pSprite->Render();
					break;
				}

				case b2Shape::e_circle:
				{
					b2CircleShape* s = (b2CircleShape*)pFix->GetShape();
					s->m_radius;
					s->m_p;

					Vect vin(s->m_p.x, s->m_p.y, 0.0f);
					Vect vout = vin * M;

					Vect2D vList;
					vList.x = MeterToPixel(vout[x]);
					vList.y = MeterToPixel(vout[y]);
					float rad = MeterToPixel(s->m_radius);

					GraphicsObject_Circle *pSprite = new GraphicsObject_Circle(Rect(vList.x, vList.y, rad, rad));
					pSprite->debugColor = pGameObj2D->debugColor;
					pSprite->Render();


				}
				break;

				}  // switch

				pFix = pFix->GetNext();

			} // while()

		}// if pBody()
	}//if HasBody()
}
void GameObjectMan::CreateSorting()
{
	//Clear this later no need to create object in stack

	GameSortBucket *pSortEffects = new GameSortBucket(GameObjectName::Effects_Sort);
	GameObjectMan::Add(pSortEffects);

	GameSortBucket *pSmokeBucket_A = new GameSortBucket(GameObjectName::SmokeBucket_A);
	GameObjectMan::Add(pSmokeBucket_A);

	GameSortBucket *pSmokeBucket_B = new GameSortBucket(GameObjectName::SmokeBucket_B);
	GameObjectMan::Add(pSmokeBucket_B);

	GameSortBucket *pSmokeBucket_A_Particle = new GameSortBucket(GameObjectName::SmokeBucket_A_Particle);
	GameObjectMan::Add(pSmokeBucket_A_Particle);

	GameSortBucket *pSmokeBucket_B_Particle = new GameSortBucket(GameObjectName::SmokeBucket_B_Particle);
	GameObjectMan::Add(pSmokeBucket_B_Particle);

	GameSortBucket *pSortBlocks = new GameSortBucket(GameObjectName::Blocks_Sort);
	GameObjectMan::Add(pSortBlocks);

	//

	GameSortBucket *pSlingBackSort = new GameSortBucket(GameObjectName::SlingShootBack_Sort);
	GameObjectMan::Add(pSlingBackSort);

	GameSortBucket *pRubberBandFrontSort = new GameSortBucket(GameObjectName::RubberBandFront_Sort);
	GameObjectMan::Add(pRubberBandFrontSort);

	//GameSortBucket *pSlingSeatSort = new GameSortBucket(GameObjectName::SlingShootSeat_Sort);
	//GameObjectMan::Add(pSlingSeatSort);

	//
	////BirdSort// Place


	GameSortBucket *pSortBirds = new GameSortBucket(GameObjectName::Birds_Sort);
	GameObjectMan::Add(pSortBirds);



	GameSortBucket *pSlingFrontSort = new GameSortBucket(GameObjectName::SlingShootFront_Sort);
	GameObjectMan::Add(pSlingFrontSort);
	

	GameSortBucket *pRubberBandBackSort = new GameSortBucket(GameObjectName::RubberBandBack_Sort);
	GameObjectMan::Add(pRubberBandBackSort);
	
	GameSortBucket *pSortStatics = new GameSortBucket(GameObjectName::StaticObjects_Sort);
	GameObjectMan::Add(pSortStatics);

	GameSortBucket *pBackGroundSort = new GameSortBucket(GameObjectName::BackGround_Sort);
	GameObjectMan::Add(pBackGroundSort);

	


}

GameObject2D * GameObjectMan::getActiveBird()
{
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert(pGOM);
	

	
	GameObject * pBucket = GameObjectMan::Find(GameObjectName::Birds_Sort);
	assert(pBucket);
	GameObject2D *pBird = 0;
	if (pBucket->getNumChildren() > 0)
	{
		pBird = (GameObject2D*)pBucket->getChild();				
		pBird = pGOM->activeBird;
	}
	
	return pBird;
}
void  GameObjectMan::setActiveBird(GameObject2D* pBird)
{
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert(pGOM);
	pGOM->activeBird = pBird;
}
