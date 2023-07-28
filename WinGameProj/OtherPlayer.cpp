#include "pch.h"
#include "OtherPlayer.h"
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
#include "SceneMgr.h"
#include "Scene.h"
#include "NetMgr.h"
void OtherPlayer::Update() 
{
	userData data=NetMgr::GetInst()->GetUserData(socketId); 
	//pos , animation 변경
	switch (data.pState)
	{
	case (int)OPLAYER_STATE::PLAYER_DASH_LEFT :
		GetAnimator()->Play(L"RunningLeft", true);
		break;
	case (int)OPLAYER_STATE::PLAYER_DASH_RIGHT:
		GetAnimator()->Play(L"RunningRight", true);
		break;
	case (int)OPLAYER_STATE::PLAYER_STAND_LEFT:
		GetAnimator()->Play(L"StandLeft", true);
		break;
	case (int)OPLAYER_STATE::PLAYER_STAND_RIGHT:
		GetAnimator()->Play(L"StandRight", true);
		break;
	case (int)OPLAYER_STATE::PLAYER_WALKING_LEFT:
		GetAnimator()->Play(L"WalkingLeft", true);
		break;
	case (int)OPLAYER_STATE::PLAYER_WALKING_RIGHT:
		GetAnimator()->Play(L"WalkingRight", true);
		break;
	}
	GetAnimator()->Update();
	SetPos(data.pos);
}

void OtherPlayer::Render(HDC hdc)
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

shared_ptr<CObject> OtherPlayer::Clone()
{
	return shared_ptr<CObject>();
}


OtherPlayer::OtherPlayer(int id)
{
	//Texture 로딩 
	
	lock_guard<std::mutex> lockGuard(resMutex);
	pTex = ResMgr::GetInst()->LoadTexture(L"Player", L"Texture\\Player\\Player.bmp");
	pLeftTex = ResMgr::GetInst()->LoadTexture(L"PlayerReverse", L"Texture\\Player\\Player_reverse.bmp");
	

	mfDuration = 0.05f;
	mfAccTime = 0.f;
	socketId = id;
	mfPacketDuration = 0.1f;
	mPacketTime = 0.f;
	pState = OPLAYER_STATE::PLAYER_STAND_RIGHT; 
}

OtherPlayer::~OtherPlayer()
{
	pTex = nullptr;
}

void OtherPlayer::AllocComp()
{
	lock_guard<std::mutex> lockGuard(resMutex); 
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
		pRunningRight->GetFrame(5).vLeftTop = pRunningRight->GetFrame(4).vLeftTop + Vec2(25, 0);
		pRunningRight->GetFrame(6).vLeftTop = pRunningRight->GetFrame(4).vLeftTop + Vec2(50, 0);

		pRunningLeft->GetFrame(2).vLeftTop = pRunningLeft->GetFrame(4).vLeftTop - Vec2(23, 0);
		pRunningLeft->GetFrame(3).vLeftTop = pRunningLeft->GetFrame(4).vLeftTop - Vec2(46, 0);
		pRunningLeft->GetFrame(4).vSlice = Vec2(28, 22);


	}


}
