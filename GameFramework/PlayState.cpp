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
	mDemonNumber=0;

	isBossSpawn = false;
	mItemPlayerVelocity = 0;

	//0607
	mCameraWheelValue = 0;

	mPlayer = new Player;

	mSkull = new Skull;

	for (int i = 0; i < DEMONNUMBER; ++i,++mDemonNumber)
	{
		mDemon[i] = new Demon(mDemonNumber);

	}

	for(int i = 0; i < mPlayer->mBulletNumber; ++i)
		mPlayer->mBullet[i]->setAlive(false);

	//mTerrain = new Terrain;
	//mTerrain = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0,100,0), "floor1", "floor.mesh");
	//mTerrain->createTerrain(mSceneMgr->getRootSceneNode(), Vector3(0,100,0), "floor1", "floor.mesh");




	_drawGridPlane();
	_setLights();
	_drawGroundPlane();
	_createParticleSystem();

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

	mTerrain[0] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(-450.0f, 730.0f, 0.0f), "crossrail", "crossrail.mesh");
	mTerrain[0]->getTerrainSceneNode()->setScale(2.0f,1.0f,2.0f);

	mTerrain[1] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(100, 0.0f, 0), "bullet", "Bullet.mesh");
	mTerrain[2] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0.f, -100.0f, 0.f), "bricks", "bricks.mesh");
	mTerrain[2]->getTerrainSceneNode()->yaw(Degree(180));
	mTerrain[3] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0.f, -100.0f, 0.f), "floor", "floor.mesh");
	mTerrain[4] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0.f, -100.0f, 0.f), "Gate", "Gate.mesh");
	mTerrain[4]->getTerrainSceneNode()->yaw(Degree(180));
	mTerrain[5] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0.f, -100.0f, 0.f), "Towers", "Towers.mesh");

	mTerrain[6] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0.f, 200.0f, 0.0f), "SkyBox", "skybox2.mesh");
	mTerrain[6]->getTerrainSceneNode()->setScale(1000.f,1000.f,1000.f);
	mTerrain[6]->getTerrainSceneNode()->yaw(Degree(180));

	mTerrain[7] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(-950.f, 0.0f, 0.0f), "ItemBox1", "WoodenBox.mesh");
	mTerrain[8] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(950.f, 0.0f, 0.0f), "ItemBox2", "TresureBox.mesh");
	mTerrain[9] = new Terrain(mSceneMgr->getRootSceneNode(), Vector3(0.f, 0.0f, 950.0f), "ItemBox4", "TresureBox.mesh");
	mTerrain[9]->getTerrainSceneNode()->yaw(Degree(90));
	

	dest = Vector3::ZERO;
	demonVelocity = 150.0f;
	bulletNumber = 0;
	speed = 500;
	

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

	if(mPlayer->getPlayerSceneNode()->getPosition().x < mTerrain[7]->getTerrainSceneNode()->getPosition().x + 50.0f)
	{
		mTerrain[7]->getTerrainSceneNode()->translate(0.0f,-500.0f,0.0f);
		mItemPlayerVelocity = 150.0f;
	}
	if(mTerrain[8]->getTerrainSceneNode()->getPosition().x - 50.0f < mPlayer->getPlayerSceneNode()->getPosition().x)
	{
		mTerrain[8]->getTerrainSceneNode()->translate(0.0f,-500.0f,0.0f);
		mPlayer->setMissilePower(20);
	}
	if(mTerrain[9]->getTerrainSceneNode()->getPosition().z - 50.0f < mPlayer->getPlayerSceneNode()->getPosition().z
		&&
		mTerrain[9]->getTerrainSceneNode()->getPosition().y == mPlayer->getPlayerSceneNode()->getPosition().y)
	{
		mTerrain[9]->getTerrainSceneNode()->translate(0.0f,-500.0f,0.0f);
		mPlayer->setHP(100);
	}






	mPlayer->bulletUpdate(evt.timeSinceLastFrame);

	for (int i = 0; i < DEMONNUMBER; i++)
	{
		mDemon[i]->trace(mPlayer->getPlayerSceneNode());
		mDemon[i]->update(evt.timeSinceLastFrame);
	}


	if(10 <= mPlayer->getHP() && isBossSpawn == false)
	{
		mBoss = new Boss;
		isBossSpawn = true;
	}
	if(isBossSpawn == true)
	{
		mBoss->update(evt.timeSinceLastFrame);
	}


	mSkull->update(evt.timeSinceLastFrame);
	mSkull->trace(mPlayer->getPlayerSceneNode());


	mSkull->update(evt.timeSinceLastFrame);
	mSkull->trace(mPlayer->getPlayerSceneNode());


	//카메라 흔들림
	mPlayer->runOut(evt.timeSinceLastFrame,mCamera);

	//충돌체크
	for(int i = 0; i < mPlayer->mBulletNumber; ++i)
	{
		if(mPlayer->mBullet[i]->getAlive() == true) //이미 충돌된 총알이 아닐 때만 충돌 체크
		{
			//데몬
			for (int j = 0; j < DEMONNUMBER; ++j)
			{
				if(mDemon[j]->collisionCheck(mPlayer->mBullet[i]->mBulletPosition))//만약 충돌하면 총알의 isAlive false처리.
				{
					mPlayer->mBullet[i];
					mPlayer->mBullet[i]->setAlive(false);

					//점수획득
					mPlayer->setHP(10);
					//충돌 애니메이션 실행
					//mDemon->getHurt(evt.timeSinceLastFrame);
					mDemon[j]->setDemonState(hurt);
					mDemon[j]->setHP(mPlayer->getMissilePower());
				}
			}
			//해골
			if(mSkull->collisionCheck(mPlayer->mBullet[i]->mBulletPosition))
			{
				mPlayer->mBullet[i];
				mPlayer->mBullet[i]->setAlive(false);

				mPlayer->setHP(10);
			}

			//보스
			if(isBossSpawn==true)
			{
				if(true == mBoss->getAlive() && mBoss->collisionCheck(mPlayer->mBullet[i]->mBulletPosition))
				{
					mPlayer->mBullet[i];
					mPlayer->mBullet[i]->setAlive(false);

					mPlayer->setHP(10);
					mBoss->getHurt(mPlayer->getMissilePower());
				}
			}
		}
	}



	return true;
}

bool PlayState::frameEnded(GameManager* game, const FrameEvent& evt)
{
	static Ogre::DisplayString currFps = L"현재 FPS: ";
	static Ogre::DisplayString avgFps = L"현재 점수: ";
	static Ogre::DisplayString bestFps = L"BOSS HP: ";
	static Ogre::DisplayString worstFps = L"포탄 파워: ";

	OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("AverageFps");
	OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("CurrFps");
	OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("BestFps");
	OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("WorstFps");

	const RenderTarget::FrameStats& stats = mRoot->getAutoCreatedWindow()->getStatistics();

	guiCurr->setCaption(currFps + StringConverter::toString(stats.avgFPS));
	guiAvg->setCaption(avgFps + StringConverter::toString(mPlayer->getHP()));
	if(isBossSpawn)
		guiBest->setCaption(bestFps + StringConverter::toString(mBoss->getBossHP()));
	guiWorst->setCaption(worstFps + StringConverter::toString(mPlayer->getMissilePower())); 
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
		if(-45.0f < mPlayer->getPlayerPosition().z && mPlayer->getPlayerPosition().z < 45.0f)
			mPlayerVelocityX = -150.0f - mItemPlayerVelocity;
		break;

	case OIS::KC_D:

		//mPlayerX = mCameraPositionX += 3.0f;
		mPlayerDirection = RIGHT;
		if(-45.0f < mPlayer->getPlayerPosition().z && mPlayer->getPlayerPosition().z < 45.0f)
			mPlayerVelocityX = 150.0f + mItemPlayerVelocity;
		break;

	case OIS::KC_W:

		//mPlayerZ = mCameraPositionZ -= 3.0f;
		mPlayerDirection = UP;
		if(-45.0f < mPlayer->getPlayerPosition().x && mPlayer->getPlayerPosition().x < 45.0f)
			mPlayerVelocityZ = -150.0f - mItemPlayerVelocity;
		break;

	case OIS::KC_S:

		//mPlayerZ = mCameraPositionZ += 3.0f;
		mPlayerDirection = DOWN;
		if(-45.0f < mPlayer->getPlayerPosition().x && mPlayer->getPlayerPosition().x < 45.0f)
			mPlayerVelocityZ = 150.0f + mItemPlayerVelocity;
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
		mPlayer->runOutStart();
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
	mLightS->setVisible(true);

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


void PlayState::_createParticleSystem(void)
{

	// fill here
	mSunNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("Sun",Ogre::Vector3(0,500,0));
	//mJetEngineNode = mSceneMgr->getSceneNode("ProfessorRoot")->createChildSceneNode("JetEngine");
	pSys = mSceneMgr->createParticleSystem("SunSystem", "Particle/Smoke");
	mSunNode->attachObject(pSys);
	//pSys = mSceneMgr->createParticleSystem("JetEngineParticle", "Particle/JetEngine");
	//mJetEngineNode->attachObject(pSys);

	//pSys = mSceneMgr->createParticleSystem("SunSystem", "Particle/Smoke");
	for (int i = 0; i < 50; i++)
	{
		sprintf(mParticleName, "particle%d", i);
		pSys = mSceneMgr->createParticleSystem(mParticleName, "Particle/Smoke");
		sprintf(mFireName, "fire%d", i);
		mfireNode[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode(mFireName,Ogre::Vector3(i*80-2000,0,-2000));
		mfireNode[i]->attachObject(pSys);
	}

}
