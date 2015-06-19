#pragma once

#define CLIENT_DESCRIPTION "Quaternion"

#include "GameState.h"
#include "Demon.h"
#include "Terrain.h"
#include "Boss.h"
#include "skull.h"

#include "windows.h"
#include "math.h"
#include "OgreVector3.h"

#include "Player.h"

#include <Ogre.h>
#include <OIS/OIS.h>

#define DEMONNUMBER 3
#define RADIAN(angle) angle * 3.14/180

enum PlayerDirection{ LEFT, RIGHT, UP, DOWN };

using namespace Ogre;

class PlayState : public GameState
{
public:
	void enter(void);
	void exit(void);

	void pause(void);
	void resume(void);

	bool frameStarted(GameManager* game, const Ogre::FrameEvent& evt);
	bool frameEnded(GameManager* game, const Ogre::FrameEvent& evt);

	bool mouseMoved(GameManager* game, const OIS::MouseEvent &e);
	bool mousePressed(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id);

	bool keyPressed(GameManager* game, const OIS::KeyEvent &e);
	bool keyReleased(GameManager* game, const OIS::KeyEvent &e);

	static PlayState* getInstance() { return &mPlayState; }

	void _createParticleSystem(void);

private:

	void _setLights(void);
	void _drawGroundPlane(void);
	void _drawGridPlane(void);


	static PlayState mPlayState;

	Ogre::Root *mRoot;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

	Ogre::Light *mLightP, *mLightD, *mLightS;

	Ogre::SceneNode* mCharacterRoot;
	Ogre::SceneNode* mCharacterYaw;
	Ogre::SceneNode* mCameraHolder;
	Ogre::SceneNode* mCameraYaw;
	Ogre::SceneNode* mCameraPitch;

	Ogre::Entity* mCharacterEntity;

	Ogre::AnimationState* mAnimationState;

	Ogre::Overlay*           mInformationOverlay;


	//추가
	Quaternion quat;

	Vector3 dest;
	Vector3 mDestination;
	Vector3 mDirection;
	Real mDistance;
	Real move;
	float demonVelocity;

	float mCameraPositionX, mCameraPositionY, mCameraPositionZ;
	float mCameraVelocity;
	AnimationState* mShootState;
	//float mPlayerX, mPlayerY, mPlayerZ;

	//0605
	float mPlayerVelocityX, mPlayerVelocityY, mPlayerVelocityZ;

	OIS::Keyboard* mKeyboard;

	/*SceneNode* Demon[50];
	Entity* dEntity[DEMONNUMBER];
	AnimationState* demonAnimationState[DEMONNUMBER];
	char name[DEMONNUMBER];*/

	SceneNode* mPlayerNode, *mPlayerBodyNode;

	SceneNode* testDemon[3];
	Entity* entity[12];
	AnimationState* testDemonAnimationState[3];

	char bName[50];
	Entity* bEntity[50];
	//Vector3 mBulletDirection[50];
	Vector3 mBulletDirection;


	SceneNode* Bullet[50];
	int bulletNumber;
	Real speed;
	bool goBullet[50];

	//클래스용 추가
	Player* mPlayer;
	Demon* mDemon;
	Boss* mBoss;
	Skull* mSkull;
	Terrain* mTerrain[10];
	PlayerDirection mPlayerDirection;

	//0607 카메라
	float mCameraWheelValue;
	
	//paticle system
	ParticleSystem* pSys;
	Ogre::SceneNode* mSunNode;

	bool isBossSpawn;
};


