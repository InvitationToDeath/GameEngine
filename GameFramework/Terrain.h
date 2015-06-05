#pragma once

#include "GameManager.h"
#include "GameState.h"

using namespace Ogre;


class Terrain
{
public:
	Terrain();
	~Terrain();

	//�θ� �����, ��ġ�� ��ġ�� ��������.
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