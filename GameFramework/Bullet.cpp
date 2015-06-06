#include "Bullet.h"


using namespace Ogre;

//-------------------------------------------
Bullet::Bullet()
{
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");

	sprintf(mName, "Bullet%d", mBulletNumber);
	mBulletEntity = mSceneMgr->createEntity(mName, "bullet.mesh");
	mBulletSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName, Vector3(Vector3::ZERO));
	mBulletSceneNode->attachObject(mBulletEntity);
	mBulletSceneNode->setScale(1,1,1);

	mBulletSceneNode->setPosition(0,0,-500);
	//mPlayerHeadSceneNode->setScale(0.2,0.2,0.2);
	
	
}
