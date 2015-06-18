#include "Demon.h"

using namespace std;

Demon::Demon()
{
	mDemonNumber=0;
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");
	demonVelocity=300.0f;


	sprintf(mName, "Demon%d", mDemonNumber);
	mDemonEntity=mSceneMgr->createEntity(mName, "Demon.mesh");
	mDemonNode=mSceneMgr->getRootSceneNode()->createChildSceneNode(mName,Vector3(Vector3::ZERO));
	mDemonNode->attachObject(mDemonEntity);
//	mDemonNode->setPosition(rand()%3000-1500, rand()%2000, -(rand()%5000+1000));
	mDemonNode->setPosition(100,500,-2000);
	mDemonAnimationState = mDemonEntity->getAnimationState("DemonIdle");
	mDemonAnimationState->setLoop(true);
	mDemonAnimationState->setEnabled(true);
	sinAngle=0;
	mAxis=(1,0,0);
	time=0;
	randomNumber=rand()%4;
	
}

void Demon::update(Ogre::Real timeSinceLastFrame)
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
	
	
	move = demonVelocity * timeSinceLastFrame;

	if(mDistance>=60){
		mDemonNode->translate( mDirection * move *  sin((sinAngle *(PI / 180))));
		mDemonNode->translate( mAxis * move *  sin((sinAngle *(PI / 180))));

		if(moveAngle>0)
			moveAngle-=1;
		else
			moveAngle=90;

		if(sinAngle>0)
			sinAngle-=10;
		else
			sinAngle=90;
	}
	mDemonAnimationState->addTime(timeSinceLastFrame);

}

bool Demon::collisionCheck(Vector3 bulletVector)//Bullet* bullet[])
{
	if( (mDemonNode->getPosition().x-50 < bulletVector.x &&	bulletVector.x < mDemonNode->getPosition().x+50) &&
		(mDemonNode->getPosition().y < bulletVector.y &&	bulletVector.y < mDemonNode->getPosition().y+150)&&
		(mDemonNode->getPosition().z < bulletVector.z &&	bulletVector.z < mDemonNode->getPosition().z+50))
	{
			cout << "악마 충돌 발생!" << endl;
			//system("cls");
			return true;
	}
	return false;
}

void Demon::trace(SceneNode* destNode)
{
	mDestination = destNode->getPosition();
	mDirection = mDestination - mDemonNode->getPosition();
	mDistance = mDirection.normalise( );
	quat = Vector3(Vector3::UNIT_Z).getRotationTo(mDirection);
	mDemonNode->setOrientation(quat);
	
	if(mDistance<=60){
		mDemonAnimationState->setEnabled(false);
		mDemonAnimationState->setLoop(false);
		//quat = Vector3(Vector3::UNIT_Z).getRotationTo(destNode->getPosition());
		mDemonAnimationState = mDemonEntity->getAnimationState("DemonAttack");
		mDemonAnimationState->setLoop(true);
		mDemonAnimationState->setEnabled(true);
	}
}

