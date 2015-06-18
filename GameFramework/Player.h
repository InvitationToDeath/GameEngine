#pragma once

#include "GameManager.h"
#include "GameState.h"
#include "Bullet.h"
#define PI 3.141592

using namespace Ogre;


class Player
{
public:
	Player();
	~Player();

	void createPlayer();
	void setHP(int hp); int getHP();
	void setPlayerPosition(float x, float y, float z); Vector3 getPlayerPosition();
	void playerHeadYaw(float yawValue); void playerHeadPitch(float pitchValue);
	SceneNode* getPlayerSceneNode();
	void fireBullet(Vector3 direction,Quaternion position);
	void playerDie();
	void bulletUpdate(Ogre::Real time);
	/*Bullet** getBullet();*/
	Bullet* mBullet[50];
	int mBulletNumber;
	void runOut(Ogre::Real time,Ogre::Camera* camera);
	void runOutStart();


protected:

private:
	int mPlayerHP, mMaxPlayerHP;
	int mPlayerVelocity;
	Vector3 mPlayerPosition;

	bool mIsPlayerDie;

	Entity* mPlayerHeadEntity;
	Entity* mPlayerBodyEntity;

	SceneNode* mPlayerHeadYawSceneNode,* mPlayerHeadPitchSceneNode;
	SceneNode* mPlayerHeadSceneNode;
	SceneNode* mPlayerBodySceneNode;
	

	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::Root* mRoot;

	bool mBulletIsFull;

	bool mRunout;
	int mSinAngle;
	int mRunoutDegree;

};