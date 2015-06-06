#pragma once

#include "GameManager.h"
#include "GameState.h"

using namespace Ogre;


class Bullet
{
public:
	Bullet();
	~Bullet();
	void fire();
	void update();

	void createPlayer();
	void setHP(int hp); int getHP();
	void setPlayerPosition(float x, float y, float z); Vector3 getPlayerPosition();
	void playerHeadYaw(float yawValue); void playerHeadPitch(float pitchValue);
	SceneNode* getPlayerSceneNode();
	void fireBullet();
	void playerDie();

protected:

private:
	int mBulletDamage;
	int mBulletVelocity;
	Vector3 mBulletPosition;

	bool mIsFire;

	Entity* mBulletEntity;
	
	SceneNode* mBulletSceneNode;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Root* mRoot;

	char mName[15];
	int mBulletNumber;

};