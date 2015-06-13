#include "Boss.h"

Boss::Boss()
{
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");

	mBossEntity = mSceneMgr->createEntity("Boss", "BossMesh.mesh");
	mBossSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("Boss", Vector3(0.0f, -3150.0f, -5000.0f));
	mBossSceneNode->attachObject(mBossEntity);
	mBossSceneNode->scale(0.3f,0.3f,0.3f);

	mBossAnimationState = mBossEntity->getAnimationState("BossSpawn");
	mBossAnimationState->setLoop(true);
	mBossAnimationState->setEnabled(true);
}
Boss::~Boss()
{

}
void Boss::update(Ogre::Real timeSinceLastFrame)
{
	mBossAnimationState->addTime(timeSinceLastFrame);
}
void Boss::setPosition(Vector3 position){
	mBossSceneNode->setPosition(position);	
}