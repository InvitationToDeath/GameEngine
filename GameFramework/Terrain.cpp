#include "Terrain.h"


using namespace Ogre;

//-----------------------------------------
Terrain::Terrain()
{
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");
}

//-----------------------------------------
Terrain::Terrain(SceneNode* terrainNode, Vector3 terrainPosition, char* terrainName, char* terrainMeshName)
{
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");

	mTerrainEntity = mSceneMgr->createEntity(terrainName, terrainMeshName);
	mTerrainSceneNode = terrainNode->createChildSceneNode(terrainName, terrainPosition);
	mTerrainSceneNode->attachObject(mTerrainEntity);
}

//-----------------------------------------
void Terrain::createTerrain(SceneNode* terrainNode, Vector3 terrainPosition, char* terrainName, char* terrainMeshName)
{
	mTerrainEntity = mSceneMgr->createEntity(terrainName, terrainMeshName);
	mTerrainSceneNode = terrainNode->createChildSceneNode(terrainName, terrainPosition);
	mTerrainSceneNode->attachObject(mTerrainEntity);
}

//-----------------------------------------
void Terrain::setTerrainPosition(float x, float y, float z)
{
	mTerrainSceneNode->setPosition(x,y,z);
}

//-----------------------------------------
Vector3 Terrain::getTerrainPosition()
{
	return mTerrainSceneNode->getPosition();
}

//-----------------------------------------
SceneNode* Terrain::getTerrainSceneNode()
{
	return mTerrainSceneNode;
}