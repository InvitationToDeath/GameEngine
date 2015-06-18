#include "PlayState.h"
#include "TitleState.h"
#include "Player.h"
#include "Boss.h"

#include <vector>




using namespace Ogre;
using namespace std;

PlayState PlayState::mPlayState;


void PlayState::enter(void)
{
	mRoot = Root::getSingletonPtr();
	mRoot->getAutoCreatedWindow()->resetStatistics();

	mSceneMgr = mRoot->getSceneManager("main");
	mCamera = mSceneMgr->getCamera("main");
	mCamera->setPosition(Ogre::Vector3::ZERO);
	//mCamera->setFOVy(Degree(30));
	//mCamera->setFarClipDistance(100.0f);


	//0607
	mCameraWheelValue = 0;

	mPlayer = new Player;
	mDemon = new Demon;
	mBoss = new Boss;
	mSkull = new Skull;

	//mTerrain = new Terrain;
	//mTerrain = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0,100,0), "floor1", "floor.mesh");
	//mTerrain->createTerrain(mSceneMgr->getRootSceneNode(), Vector3(0,100,0), "floor1", "floor.mesh");




	_drawGridPlane();
	_setLights();
	_drawGroundPlane();

	mInformationOverlay = OverlayManager::getSingleton().getByName("Overlay/Information");
	mInformationOverlay->show();

	mCharacterRoot = mSceneMgr->getRootSceneNode()->createChildSceneNode("ProfessorRoot");
	mCharacterYaw = mCharacterRoot->createChildSceneNode("ProfessorYaw");

	mCameraYaw = mCharacterRoot->createChildSceneNode("CameraYaw", Vector3(0.0f, 120.0f, 0.0f));
	mCameraPitch = mCameraYaw->createChildSceneNode("CameraPitch");
	mCameraHolder = mCameraPitch->createChildSceneNode("CameraHolder", Vector3(0.0f, 80.0f, 500.0f));


	mCameraHolder->attachObject(mCamera);
	mCamera->lookAt(mCameraYaw->getPosition());


	//플레이어, 지형 (클래스 생성자로 모두 변경)

	mTerrain[0] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(-230.0f, 730.0f, 0.0f), "crossrail", "crossrail.mesh");
	//mTerrain[0]->getTerrainSceneNode()->setScale(0.5,0.5,0.5);
	mTerrain[1] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(100, 0.0f, 0), "bullet", "Bullet.mesh");
	mTerrain[2] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0.f, -100.0f, 0.f), "bricks", "bricks.mesh");
	mTerrain[3] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0.f, -100.0f, 0.f), "floor", "floor.mesh");
	mTerrain[4] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0.f, -100.0f, 0.f), "Gate", "Gate.mesh");
	mTerrain[5] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0.f, -100.0f, 0.f), "Towers", "Towers.mesh");

	mTerrain[6] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0.f, 100.0f, 0.f), "Bullet1z", "IronBall.mesh");


	/*entity[3] = mSceneMgr->createEntity("crossrail", "crossrail.mesh");
	SceneNode* crossrail = mSceneMgr->getRootSceneNode()->createChildSceneNode("Crossrail", Vector3(-113.0f, 373.0f, 0.0f));
	crossrail->attachObject(entity[3]);
	crossrail->setScale(0.5, 0.5, 0.5);

	entity[6] = mSceneMgr->createEntity("bullet", "bullet.mesh");
	SceneNode* bullet = mSceneMgr->getRootSceneNode()->createChildSceneNode("bullet", Vector3(100, 0.0f, 0));
	bullet->attachObject(entity[6]);

	entity[7] = mSceneMgr->createEntity("bricks", "bricks.mesh");
	SceneNode* bricks = mSceneMgr->getRootSceneNode()->createChildSceneNode("bricks", Vector3(0.f, -100.0f, 0.f));
	bricks->attachObject(entity[7]);

	entity[8] = mSceneMgr->createEntity("floor", "floor.mesh");
	SceneNode* floor = mSceneMgr->getRootSceneNode()->createChildSceneNode("floor", Vector3(0.f, -100.0f, 0.f));
	floor->attachObject(entity[8]);

	entity[9] = mSceneMgr->createEntity("Gate", "Gate.mesh");
	SceneNode* Gate = mSceneMgr->getRootSceneNode()->createChildSceneNode("Gate", Vector3(0.f, -100.0f, 0.f));
	Gate->attachObject(entity[9]);

	entity[10] = mSceneMgr->createEntity("Towers", "Towers.mesh");
	SceneNode* Towers = mSceneMgr->getRootSceneNode()->createChildSceneNode("Towers", Vector3(0.f, -100.0f, 0.f));
	Towers->attachObject(entity[10]);*/



	////총알 생성
	//for (int i = 0; i<50; ++i){
	//	sprintf(bName, "Bullet%d", i);
	//	bEntity[i] = mSceneMgr->createEntity(bName, "IronBall.mesh");
	//	Bullet[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode(bName, Vector3(Vector3::ZERO));
	//	Bullet[i]->attachObject(bEntity[i]);
	//	/*	Demon[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode(bName,Vector3(Vector3::ZERO));
	//	Demon[i]->attachObject(bEntity[i]);
	//	Demon[i]->setPosition(0,0,100);
	//	Demon[i]->setPosition(rand()%3000-1500, rand()%2000, -(rand()%5000+1000));*/
	//}
	////비활성화
	//for (int i = 0; i < 50; i++)
	//{
	//	goBullet[i] = false;
	//}


	dest = Vector3::ZERO;
	demonVelocity = 150.0f;
	bulletNumber = 0;
	speed = 500;

	// 카메라 시작 위치 조정
	//mCameraPositionX = 0.f;
	//mCameraPositionY = 200.f;
	//mCameraPositionZ = 0.f;
	//mCamera->setPosition(mCameraPositionX, mCameraPositionY, mCameraPositionZ);

	/*
	mPlayerX=0;
	mPlayerY=30;
	mPlayerZ=0;*/



	//Vector3 dest(Vector3::ZERO);


}

void PlayState::exit(void)
{
	// Fill Here -----------------------------
	mSceneMgr->clearScene();
	mInformationOverlay->hide();
	// ---------------------------------------
	//delete mPlayer;
}

void PlayState::pause(void)
{
}

void PlayState::resume(void)
{
}

bool PlayState::frameStarted(GameManager* game, const FrameEvent& evt)
{

	//플레이어 이동 로직.
	//mPlayer->getPlayerSceneNode()->translate(mPlayerX,mPlayerY,mPlayerZ);
	mPlayer->getPlayerSceneNode()->translate(mPlayerVelocityX * evt.timeSinceLastFrame, mPlayerVelocityY * evt.timeSinceLastFrame, mPlayerVelocityZ * evt.timeSinceLastFrame);
	mCamera->setPosition(mPlayer->getPlayerPosition().x, mPlayer->getPlayerPosition().y + 200, mPlayer->getPlayerPosition().z + 50 + mCameraWheelValue);

	////총알 발사
	//for (int i = 0; i < 50; i++)
	//{
	//	if (goBullet[i] == true){
	//		//mBulletDirection.z=-mBulletDirection.z;

	//		Bullet[i]->translate(mBulletDirection[i].normalisedCopy() * 1000 * evt.timeSinceLastFrame, Node::TransformSpace::TS_LOCAL);
	//		//Bullet[i]->translate(0,0,-speed*evt.timeSinceLastFrame);
	//	}
	//}

	mPlayer->bulletUpdate(evt.timeSinceLastFrame);
	mDemon->trace(mPlayer->getPlayerSceneNode());
	mDemon->update(evt.timeSinceLastFrame);
	mBoss->update(evt.timeSinceLastFrame);
<<<<<<< HEAD
	mSkull->update(evt.timeSinceLastFrame);
	mSkull->trace(mPlayer->getPlayerSceneNode());
=======

	//데몬 충돌체크
	for(int i = 0; i < mPlayer->mBulletNumber; ++i)
		mDemon->collisionCheck(mPlayer->mBullet[i]->mBulletPosition);//mPlayer->mBullet);


>>>>>>> origin/master
	return true;
}

bool PlayState::frameEnded(GameManager* game, const FrameEvent& evt)
{
	static Ogre::DisplayString currFps = L"현재 FPS: ";
	static Ogre::DisplayString avgFps = L"평균 FPS: ";
	static Ogre::DisplayString bestFps = L"최고 FPS: ";
	static Ogre::DisplayString worstFps = L"최저 FPS: ";

	OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("AverageFps");
	OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("CurrFps");
	OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("BestFps");
	OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("WorstFps");

	const RenderTarget::FrameStats& stats = mRoot->getAutoCreatedWindow()->getStatistics();

	guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
	guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
	guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS));
	guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS)); 
	//추가

	//mKeyboard->capture()
	return true;
}


bool PlayState::keyReleased(GameManager* game, const OIS::KeyEvent &e)
{
	switch (e.key)
	{

	case OIS::KC_A:
		//if(LEFT == mPlayerDirection && 0 != mPlayerVelocityX)
		mPlayerVelocityX = 0.0f;
		break;

	case OIS::KC_D:
		//if(RIGHT == mPlayerDirection && 0 != mPlayerVelocityX)
		mPlayerVelocityX = 0.0f;
		break;

	case OIS::KC_W:
		//if(UP == mPlayerDirection && 0 != mPlayerVelocityZ)
		mPlayerVelocityZ = 0.0f;

		break;

	case OIS::KC_S:
		//if(DOWN == mPlayerDirection && 0 != mPlayerVelocityZ)
		mPlayerVelocityZ = 0.0f;

		break;
	}




	return true;
}

bool PlayState::keyPressed(GameManager* game, const OIS::KeyEvent &e)
{
	// Fill Here -------------------------------------------
	switch (e.key)
	{
	case OIS::KC_ESCAPE:
		game->changeState(TitleState::getInstance());
		break;

	case OIS::KC_A:

		//mCameraPositionX -= 3.0f;
		mPlayerDirection = LEFT;
		mPlayerVelocityX = -150.0f;
		break;

	case OIS::KC_D:

		//mPlayerX = mCameraPositionX += 3.0f;
		mPlayerDirection = RIGHT;
		mPlayerVelocityX = 150.0f;
		break;

	case OIS::KC_W:

		//mPlayerZ = mCameraPositionZ -= 3.0f;
		mPlayerDirection = UP;
		mPlayerVelocityZ = -150.0f;
		break;

	case OIS::KC_S:

		//mPlayerZ = mCameraPositionZ += 3.0f;
		mPlayerDirection = DOWN;
		mPlayerVelocityZ = 150.0f;
		break;

	case OIS::KC_1:
		{
			static float a = 0.0f;
			a = (a >= 1.0f) ? 0.0f : a + 0.1f;
			mSceneMgr->setAmbientLight(ColourValue(a, a, a));
			mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
		}
		break;
	case OIS::KC_2: mLightD->setVisible(!mLightD->getVisible()); break;
	case OIS::KC_3: mLightP->setVisible(!mLightP->getVisible()); break;
	case OIS::KC_4: mLightS->setVisible(!mLightS->getVisible()); break;
	
}
//mCamera->setPosition(mPlayer->getPlayerPosition().x, mPlayer->getPlayerPosition().y, mPlayer->getPlayerPosition().z);

return true;
}

bool PlayState::mousePressed(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if (e.state.buttonDown(OIS::MB_Left)) {
		//mBulletDirection[bulletNumber] = mCamera->getPosition();
		//goBullet[bulletNumber] = true;
		////0606 수정
		//Bullet[bulletNumber]->setPosition(mPlayer->getPlayerPosition().x, mPlayer->getPlayerPosition().y + 100, mPlayer->getPlayerPosition().z);
		//Bullet[bulletNumber]->setOrientation(mCamera->getOrientation());
		//mBulletDirection[bulletNumber].z = -mBulletDirection[bulletNumber].z;
		//bulletNumber++;

		//if (bulletNumber >= 50)
		//	bulletNumber = 0;


		//mBulletDirection = mCamera->getPosition();
		////goBullet[bulletNumber] = true;
		////0606 수정
		//Bullet[bulletNumber]->setPosition(mPlayer->getPlayerPosition().x, 
		//	mPlayer->getPlayerPosition().y + 100, mPlayer->getPlayerPosition().z);
		//Bullet[bulletNumber]->setOrientation(mCamera->getOrientation());
		//mBulletDirection.z = -mBulletDirection.z;
		//bulletNumber++;

		//if (bulletNumber >= 50)
		//	bulletNumber = 0;

		mPlayer->fireBullet(mCamera->getPosition(),mCamera->getOrientation());

	}


	return true;
}

bool PlayState::mouseReleased(GameManager* game, const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}


bool PlayState::mouseMoved(GameManager* game, const OIS::MouseEvent &e)
{

	mCamera->yaw(Degree(-e.state.X.rel * 0.1));
	mCamera->pitch(Degree(-e.state.Y.rel * 0.1));

	//클래스 추가.
	mPlayer->playerHeadYaw(-e.state.X.rel * 0.1);
	mPlayer->playerHeadPitch(-e.state.Y.rel * 0.1);

	//mCamera->moveRelative(Ogre::Vector3(0, 0, -e.state.Z.rel * 0.1f));
	mCameraWheelValue += -e.state.Z.rel * 0.1f;

	return true;
}



void PlayState::_setLights(void)
{
	/*mSceneMgr->setAmbientLight(ColourValue(0.7f, 0.7f, 0.7f));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	mLightD = mSceneMgr->createLight("LightD");
	mLightD->setType(Light::LT_DIRECTIONAL);
	mLightD->setDirection(Vector3(1, -2.0f, -1));
	mLightD->setVisible(true);*/


	mSceneMgr->setAmbientLight(ColourValue(0.3f, 0.3f, 0.3f));
	mLightD = mSceneMgr->createLight("LightD");
	mLightD->setType(Light::LT_DIRECTIONAL);
	mLightD->setDirection( Vector3( 1, -2.0f, -1 ) );
	mLightD->setVisible(false);
	mLightP = mSceneMgr->createLight("LightP");
	mLightP->setType( Light::LT_POINT );
	mLightP->setPosition( Vector3(-250, 50, 250) );
	mLightP->setVisible(true);
	mLightS = mSceneMgr->createLight("LightS");
	mLightS->setType( Light::LT_SPOTLIGHT );
	mLightS->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
	mLightS->setPosition( Vector3( 250, 900, 250) );
	mLightS->setSpotlightRange( Degree(10), Degree(80));
	mLightS->setVisible(false);

	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
}

void PlayState::_drawGroundPlane(void)
{
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"Ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		500, 500,
		1, 1,
		true, 1, 5, 5,
		Vector3::NEGATIVE_UNIT_Z
		);

}

void PlayState::_drawGridPlane(void)
{
	// 좌표축 표시
	Ogre::Entity* mAxesEntity = mSceneMgr->createEntity("Axes", "axes.mesh");
	mSceneMgr->getRootSceneNode()->createChildSceneNode("AxesNode", Ogre::Vector3(0, 0, 0))->attachObject(mAxesEntity);
	mSceneMgr->getSceneNode("AxesNode")->setScale(5, 5, 5);

	Ogre::ManualObject* gridPlane = mSceneMgr->createManualObject("GridPlane");
	Ogre::SceneNode* gridPlaneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GridPlaneNode");

	Ogre::MaterialPtr gridPlaneMaterial = Ogre::MaterialManager::getSingleton().create("GridPlanMaterial", "General");
	gridPlaneMaterial->setReceiveShadows(false);
	gridPlaneMaterial->getTechnique(0)->setLightingEnabled(true);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setDiffuse(1, 1, 1, 0);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setAmbient(1, 1, 1);
	gridPlaneMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1, 1, 1);

	gridPlane->begin("GridPlaneMaterial", Ogre::RenderOperation::OT_LINE_LIST);
	for (int i = 0; i<21; i++)
	{
		gridPlane->position(-500.0f, 0.0f, 500.0f - i * 50);
		gridPlane->position(500.0f, 0.0f, 500.0f - i * 50);

		gridPlane->position(-500.f + i * 50, 0.f, 500.0f);
		gridPlane->position(-500.f + i * 50, 0.f, -500.f);
	}

	gridPlane->end();

	gridPlaneNode->attachObject(gridPlane);
}