#include "Demon.h"

Demon::Demon()
{
	mDemonNumber=0;
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");
	demonVelocity=300.0f;


	sprintf(mName, "Demon%d", mDemonNumber);
	mDemonEntity=mSceneMgr->createEntity(mName, "GEdemon.mesh");
	mDemonNode=mSceneMgr->getRootSceneNode()->createChildSceneNode(mName,Vector3(Vector3::ZERO));
	mDemonNode->attachObject(mDemonEntity);
//	mDemonNode->setPosition(rand()%3000-1500, rand()%2000, -(rand()%5000+1000));
	mDemonNode->setPosition(100,100,-2000);
	mDemonAnimationState = mDemonEntity->getAnimationState("idle");
	mDemonAnimationState->setLoop(true);
	mDemonAnimationState->setEnabled(true);
	sinAngle=0;
}

void Demon::update(Ogre::Real timeSinceLastFrame)
{
	move = demonVelocity * timeSinceLastFrame;
	if(mDistance>=40){
		mDemonNode->translate( mDirection * move *  sin((sinAngle *(PI / 180))));	
		if(sinAngle<90)
			sinAngle+=10;
		else
			sinAngle=0;
	}
	mDemonAnimationState->addTime(timeSinceLastFrame);
	
	
}

void Demon::trace(SceneNode* destNode)
{
	mDestination = destNode->getPosition();
	mDirection = mDestination - mDemonNode->getPosition();
	mDistance = mDirection.normalise( );
	quat = Vector3(Vector3::UNIT_Z).getRotationTo(destNode->getPosition());
	mDemonNode->setOrientation(quat);
	//std::cout<<quat<<std::endl;
	std::cout<<mDistance<<std::endl;
	if(mDistance<=40){
		mDemonAnimationState->setEnabled(false);
		mDemonAnimationState->setLoop(false);
		
		mDemonAnimationState = mDemonEntity->getAnimationState("atk");
		mDemonAnimationState->setLoop(true);
		mDemonAnimationState->setEnabled(true);
	}
}

