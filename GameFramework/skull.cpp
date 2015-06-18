#include "Skull.h"

Skull::Skull()
{
	mSkullNumber=0;
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");
	SkullVelocity=300.0f;


	sprintf(mName, "Skull%d", mSkullNumber);
	mSkullEntity=mSceneMgr->createEntity(mName, "Skull.mesh");
	mSkullNode=mSceneMgr->getRootSceneNode()->createChildSceneNode(mName,Vector3(Vector3::ZERO));
	mSkullNode->attachObject(mSkullEntity);
//	mDemonNode->setPosition(rand()%3000-1500, rand()%2000, -(rand()%5000+1000));
	mSkullNode->setPosition(30,500,-2000);
	mSkullNode->setScale(5,5,5);
	//mSkullAnimationState = mSkullEntity->getAnimationState("DemonIdle");
	//mSkullAnimationState->setLoop(true);
	//mSkullAnimationState->setEnabled(true);
	sinAngle=0;
	mAxis=(1,0,0);
	time=0;
	randomNumber=rand()%4;
	
}

void Skull::update(Ogre::Real timeSinceLastFrame)
{
	time+=timeSinceLastFrame;
	if(time>=randomNumber){
		mAxis.x=rand()%100-50;
		mAxis.x=mAxis.x* timeSinceLastFrame;

		mAxis.y=rand()%100-50;
		mAxis.y=mAxis.y* timeSinceLastFrame;

		time=0;
		randomNumber=rand()%2;
	}
	
	
	move = SkullVelocity * timeSinceLastFrame;

	if(mDistance>=60){
		mSkullNode->translate( mDirection * move *  sin((sinAngle *(PI / 180))));
		mSkullNode->translate( mAxis * move *  sin((sinAngle *(PI / 180))));

		if(moveAngle>0)
			moveAngle-=1;
		else
			moveAngle=90;

		if(sinAngle>0)
			sinAngle-=10;
		else
			sinAngle=90;
	}
	//mSkullAnimationState->addTime(timeSinceLastFrame);

}

void Skull::trace(SceneNode* destNode)
{
	mDestination = destNode->getPosition();
	mDirection = mDestination - mSkullNode->getPosition();
	mDistance = mDirection.normalise( );
	quat = Vector3(Vector3::UNIT_Z).getRotationTo(mDirection);
	mSkullNode->setOrientation(quat);
	
	//if(mDistance<=60){
	//	mSkullAnimationState->setEnabled(false);
	//	mSkullAnimationState->setLoop(false);
	//	//quat = Vector3(Vector3::UNIT_Z).getRotationTo(destNode->getPosition());
	//	mSkullAnimationState = mSkullEntity->getAnimationState("DemonAttack");
	//	mSkullAnimationState->setLoop(true);
	//	mSkullAnimationState->setEnabled(true);
	//}
}

