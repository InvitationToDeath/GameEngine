#include "Boss.h"

using namespace std;

//---------------------------------
Boss::Boss()
{
	mRoot = Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("main");

	mBossEntity = mSceneMgr->createEntity("Boss", "Bossmon.mesh");
	mBossSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("Boss", Vector3(0.0f, -3150.0f, -5000.0f));
	mBossSceneNode->attachObject(mBossEntity);
	mBossSceneNode->scale(0.3f,0.3f,0.3f);

	mBossAnimationState = mBossEntity->getAnimationState("BossSpawn");
	mBossAnimationState->setLoop(true);
	mBossAnimationState->setEnabled(true);
}
//---------------------------------
Boss::~Boss()
{

}
//---------------------------------
void Boss::update(Ogre::Real timeSinceLastFrame)
{
	mBossAnimationState->addTime(timeSinceLastFrame);
}
//---------------------------------
bool Boss::collisionCheck(Vector3 bulletVector)//Bullet* bullet[])
{
	//cout << mBossSceneNode->getPosition()<<endl;
	if( /*(mBossSceneNode->getPosition().x-50 < bulletVector.x &&	bulletVector.x < mBossSceneNode->getPosition().x+50) &&
		(mBossSceneNode->getPosition().y < bulletVector.y &&	bulletVector.y < mBossSceneNode->getPosition().y+150)&&
		(mBossSceneNode->getPosition().z < bulletVector.z &&	bulletVector.z < mBossSceneNode->getPosition().z+50)*/
		(-450.f < bulletVector.x &&	bulletVector.x < 450.f) &&
		(650.f < bulletVector.y &&	bulletVector.y < 1600.f)&&
		(-3525.f < bulletVector.z &&	bulletVector.z < -3500.f)
		||
		(-150.f < bulletVector.x &&	bulletVector.x < 150.f) &&
		(1600.f < bulletVector.y &&	bulletVector.y < 2300.f)&&
		(-3520.f < bulletVector.z &&	bulletVector.z < -3500.f)
		)
	{
			cout << "보스 충돌 발생!" << endl;
			//system("cls");
			return true;
	}
	return false;
}
//---------------------------------
void Boss::setPosition(Vector3 position){
	mBossSceneNode->setPosition(position);	
}