#include "pch.h"
#include "Player.h"
#include "TimeMgr.h"
#include "Missile.h"
#include "PathMgr.h"
#include "Texture.h"
#include "ResMgr.h"
#include "Collider.h"
#include "func.h"
#include "Animator.h"
#include "Animation.h"
#include "NetMgr.h"
#include "Packet.h"
void Player::Update()
{
	Vec2 vPos = GetPos();
	
	

	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEYSTATE::HOLD)
	{
		vPos.x += 100.f * TimeMgr::GetInst()->GetDelTime();
		
		mfAccTime = 0.f;
		if (KEY_CHECK(KEY::LEFT, KEYSTATE::TAP))
		{
			GetAnimator()->Play(L"WalkingLeft", true);
			pState = PLAYER_STATE::PLAYER_WALKING_LEFT; 
			mCurKey = KEY::LEFT;
		}
		else {
			if (!mDashCheck)
			{
				GetAnimator()->Play(L"WalkingRight", true);
			}
			else {
				vPos.x += 170.f * TimeMgr::GetInst()->GetDelTime();
			}

			pState = PLAYER_STATE::PLAYER_WALKING_RIGHT;
			mCurKey = KEY::RIGHT; 
		
		}
	}
	
	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEYSTATE::HOLD)
	{
		mfAccTime = 0.f;
		vPos.x -= 100.f * TimeMgr::GetInst()->GetDelTime();
		if (KEY_CHECK(KEY::RIGHT, KEYSTATE::TAP))
		{
			
			pState = PLAYER_STATE::PLAYER_WALKING_RIGHT;
			GetAnimator()->Play(L"WalkingRight", true);
			mCurKey = KEY::RIGHT;
		}
		else {
			
			pState = PLAYER_STATE::PLAYER_WALKING_LEFT;
			if (!mDashCheck)
			{
				GetAnimator()->Play(L"WalkingLeft", true);
			}
			else {
				vPos.x -= 170.f * TimeMgr::GetInst()->GetDelTime();
			}
			mCurKey = KEY::LEFT;
		}

	}
	//키를 한번 누를 때

	if (CKeyMgr::GetInst()->GetKeyState(KEY::UP) == KEYSTATE::HOLD)
	{
		vPos.y -= 200.f * TimeMgr::GetInst()->GetDelTime();
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY::DOWN) == KEYSTATE::HOLD)
	{
		vPos.y += 200.f * TimeMgr::GetInst()->GetDelTime();
	}

	if (KEY_CHECK(KEY::SPACE, KEYSTATE::TAP))
	{
		CreateMissile();
	}



	//키를 뗄 때
	if (KEY_CHECK(KEY::RIGHT, KEYSTATE::AWAY))
	{
		if (KEY_CHECK(KEY::LEFT, KEYSTATE::NONE))
		{
			GetAnimator()->Play(L"StandRight", true);
			pState = PLAYER_STATE::PLAYER_STAND_RIGHT;
			mDashCheck = true;
		}

		mCurKey = KEY::RIGHT;
	}
	else if (KEY_CHECK(KEY::LEFT, KEYSTATE::AWAY))
	{
		if (KEY_CHECK(KEY::RIGHT, KEYSTATE::NONE))
		{
			GetAnimator()->Play(L"StandLeft", true);
			pState = PLAYER_STATE::PLAYER_STAND_LEFT;
			mDashCheck = true;
		}
		mCurKey = KEY::LEFT;
	}

	

	if (mDashCheck)
	{
		mfAccTime += TimeMgr::GetInst()->GetDelTime();
		if (mfAccTime > mfDuration )
		{
			

			mfAccTime = 0.f;
			mDashCheck = false;
			mCurKey = KEY::ESC;
		}
		else {
			if (mCurKey == KEY::RIGHT)
			{
				if (KEY_CHECK(KEY::RIGHT, KEYSTATE::TAP))
				{
					GetAnimator()->Play(L"RunningRight", true);
					pState = PLAYER_STATE::PLAYER_DASH_RIGHT;
				}
			}
			else if (mCurKey == KEY::LEFT)
			{
				if (KEY_CHECK(KEY::LEFT, KEYSTATE::TAP))
				{
					GetAnimator()->Play(L"RunningLeft", true);
					pState = PLAYER_STATE::PLAYER_DASH_LEFT;
				}
			}
		}
	}

	

	//패킷 전송 속도 제한 
	mPacketTime += TimeMgr::GetInst()->GetDelTime(); 
	if (mPacketTime > mfPacketDuration) 
	{ 
		mPacketTime = 0.f;  
		MoveToPacket header; 
		header.Init(NetMgr::GetInst()->myId); 
		header.pos = vPos; 
		if (pState == PLAYER_STATE::PLAYER_DASH_LEFT)
			return;
		header.pState = pState;
		NetMgr::GetInst()->SendMoveToPacket(header); 
	}
	//


	GetAnimator()->Update();
	SetPos(vPos);
}

void Player::Render(HDC hdc)
{
	//Vec2 vPos = GetPos(); 
	//Vec2 vScale = GetScale();
	
	//int width = (int)pTex->GetWidth();
	//int height = (int)pTex->GetHeight();


	//TransparentBlt(hdc,
	//					(int)(vPos.x - (float)(width / 2)), 
	//					int(vPos.y - (float)(height / 2)), 
	//					width, 
	//					height, 
	//					pTex->GetDC(), 
	//					0,
	//					0,
	//					width,
	//					height,
	//					RGB(255, 0, 255));

	ComponentRender(hdc);

}

void Player::CreateMissile()
{
	Vec2 vMissilePos=GetPos(); 
	vMissilePos.y -= GetScale().y / 2.f;
	shared_ptr<Missile> pMissile = make_shared<Missile>();
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, 1.f));
	pMissile->SetName(L"Missile");
	pMissile->Init();
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

Player::Player()
{
	//Texture 로딩 
	pTex=ResMgr::GetInst()->LoadTexture(L"Player",L"Texture\\Player\\Player.bmp"); 
	pLeftTex=ResMgr::GetInst()->LoadTexture(L"PlayerReverse",L"Texture\\Player\\Player_reverse.bmp"); 
	mfDuration = 0.05f;
	mfAccTime = 0.f;
	
	mfPacketDuration = 0.04f;
	mPacketTime = 0.f;
	pState = PLAYER_STATE::PLAYER_STAND_RIGHT;
}

Player::~Player()
{
	pTex=nullptr;	
}

void Player::AllocComp()
{
	CreateCollider();
	CreateRigidBody();
	shared_ptr<Collider> pCollider = GetCollider();
	pCollider->SetScale(Vec2(23.f, 23.f));
	pCollider->SetOffsetPos(Vec2(0, 0));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WalkingRight", pTex, Vec2(5, 56), Vec2(23, 23), Vec2(23, 0), 10, 0.1f);
	GetAnimator()->CreateAnimation(L"WalkingLeft", pLeftTex, Vec2(732, 56), Vec2(23, 23), Vec2(-23, 0), 10, 0.1f);
	GetAnimator()->CreateAnimation(L"StandRight", pTex, Vec2(4, 7), Vec2(24, 24), Vec2(24, 0), 2, 4.f);
	GetAnimator()->CreateAnimation(L"StandLeft", pLeftTex, Vec2(732, 7), Vec2(24, 24), Vec2(-24, 0), 2, 4.f);
	GetAnimator()->CreateAnimation(L"RunningRight", pTex, Vec2(2, 80), Vec2(23, 23), Vec2(23, 0), 8, 0.08f);
	GetAnimator()->CreateAnimation(L"RunningLeft", pLeftTex, Vec2(733, 80), Vec2(23, 23), Vec2(-23, 0), 8, 0.08f);
	//Animation Settings
	{
		shared_ptr<Animation> pStandRight = GetAnimator()->FindAnimation(L"StandRight"); 
		shared_ptr<Animation> pStandLeft = GetAnimator()->FindAnimation(L"StandLeft");  
		shared_ptr<Animation> pRunningRight = GetAnimator()->FindAnimation(L"RunningRight"); 
		shared_ptr<Animation> pRunningLeft = GetAnimator()->FindAnimation(L"RunningLeft"); 
		GetAnimator()->Play(L"StandRight", true);
		pStandRight->GetFrame(1).fDuration = .3f; 
		pStandLeft->GetFrame(1).fDuration = .3f;
		pRunningRight->GetFrame(4).vSlice = Vec2(28, 22); 
		pRunningRight->GetFrame(5).vLeftTop = pRunningRight->GetFrame(4).vLeftTop+Vec2(25,0); 
		pRunningRight->GetFrame(6).vLeftTop = pRunningRight->GetFrame(4).vLeftTop+Vec2(50,0);

		pRunningLeft->GetFrame(2).vLeftTop = pRunningLeft->GetFrame(4).vLeftTop - Vec2(23, 0); 
		pRunningLeft->GetFrame(3).vLeftTop = pRunningLeft->GetFrame(4).vLeftTop - Vec2(46, 0);
		pRunningLeft->GetFrame(4).vSlice = Vec2(28, 22); 


	}


}
