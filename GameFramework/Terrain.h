#pragma once

#include "GameManager.h"
#include "GameState.h"

using namespace Ogre;


class Terrain
{
public:
	Terrain();
	~Terrain();

	//부모 씬노드, 배치할 위치를 전달해줌.
	void createTerrain(SceneManager*, Vector3);
	void setTerrainPosition(float x, float y, float z); Vector3 getTerrainPosition();
	SceneNode* getTerrainSceneNode();

protected:

private:
	Vector3 mTerrainPosition;
	Entity* mTerrainEntity;
	SceneNode* mTerrainSceneNode;


	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::Root* mRoot;
};