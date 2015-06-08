#include "Player.h"


using namespace Ogre;

//-------------------------------------------
Player::Player()
{
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");
	mCamera = mSceneMgr->getCamera("main");


	mPlayerBodyEntity = mSceneMgr->createEntity("TurretBody1", "TurretBody.mesh");
	mPlayerBodySceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("TurretBody1", Vector3(0.0f, 0.0f, 0.0f));
	mPlayerBodySceneNode->attachObject(mPlayerBodyEntity);
	mPlayerBodyEntity->setCastShadows(true);
	//mPlayerBodySceneNode->setScale(0.2,0.2,0.2);

	mPlayerHeadYawSceneNode = mPlayerBodySceneNode->createChildSceneNode("PlayerHeadYaw",Vector3(0.0f,0.0f,0.0f));
	mPlayerHeadPitchSceneNode = mPlayerHeadYawSceneNode->createChildSceneNode("PlayerHeadPitch");

	mPlayerHeadEntity = mSceneMgr->createEntity("TurretHead1", "TurretHead.mesh");
	mPlayerHeadSceneNode= mPlayerHeadPitchSceneNode->createChildSceneNode("Player1", Vector3(0.0f, -10.0f, 0.0f));
	mPlayerHeadSceneNode->attachObject(mPlayerHeadEntity);
	mPlayerHeadEntity->setCastShadows(true);
	//mPlayerHeadSceneNode->setScale(0.2,0.2,0.2);
	mPlayerHeadSceneNode->yaw(Degree(180.0f));

	bullet= new Bullet();

}

//-------------------------------------------
void Player::createPlayer()
{

}

//-------------------------------------------
void setHP(int hp)
{

}

//-------------------------------------------
int Player::getHP()
{
	return 0;
}

//-------------------------------------------
void Player::setPlayerPosition(float x, float y, float z)
{
	mPlayerBodySceneNode->setPosition(x, y, z);
}

//-------------------------------------------
Vector3 Player::getPlayerPosition()
{
	return mPlayerBodySceneNode->getPosition();
}

//-------------------------------------------
void Player::playerHeadYaw(float yawValue)
{
	mPlayerHeadYawSceneNode->yaw(Degree(yawValue));
}

//-------------------------------------------
void Player::playerHeadPitch(float pitchValue)
{
	mPlayerHeadPitchSceneNode->pitch(Degree(pitchValue));
}

//-------------------------------------------
SceneNode* Player::getPlayerSceneNode()
{
	return mPlayerBodySceneNode;
}

//-------------------------------------------
void Player::fireBullet()
{

}

//-------------------------------------------
void Player::playerDie()
{

}