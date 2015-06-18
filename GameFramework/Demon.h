#pragma once

#include <Ogre.h>
#include <OIS/OIS.h>
#include <iostream>
#include "Player.h"
#define PI 3.141592

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console" )
using namespace Ogre;

class Demon 
{
public:
	Demon();
	~Demon();
	void update(Ogre::Real timeSinceLastFrame);
	bool collisionCheck(Vector3 bulletVector);//Bullet* bullet[]);
	void setPosition(Vector3 position){
		mDemonNode->setPosition(position);	
	}
	void trace(SceneNode* destNode);
private:
	Ogre::SceneManager* mSceneMgr;
	SceneNode* mDemonNode;
	Entity* mDemonEntity;
	AnimationState* mDemonAnimationState;
	Ogre::Root *mRoot;

	char mName[15];
	int mDemonNumber;

	Quaternion prevQuat;
	Quaternion quat;

	Vector3 dest;
	Vector3 mDestination;
	Vector3 mDirection;
	Real mDistance;
	Real move;
	float demonVelocity;
	float sinAngle;
	float moveAngle;
	
	float time;
	Vector3 mAxis;
	int randomNumber;
};


	