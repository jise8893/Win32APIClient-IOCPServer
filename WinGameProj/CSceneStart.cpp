#include "pch.h"
#include "CSceneStart.h"
#include "CObject.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"
#include "Texture.h"
#include "PathMgr.h"
#include "CollisionMgr.h"
#include "CKeyMgr.h"
#include "func.h"
#include "Camera.h"
void CSceneStart::Update()
{
	Scene::Update();//�θ� Ŭ���� ����� ȣ��
	if (KEY_CHECK(KEY::ENTER, KEYSTATE::TAP))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_CHECK(KEY::LBTN,KEYSTATE::TAP)) 
	{
		Vec2 vMousePos = MOUSE_POS;
		Vec2 vLookAt = Camera::GetInst()->GetRealPos(vMousePos);
		//Camera::GetInst()->SetLookAt(vLookAt); 
	}

}
void CSceneStart::Enter()
{
	
	//Object �߰�
	shared_ptr<Player> pObj = make_shared<Player>();
	pObj->SetPos(Vec2{ 640.f,374.f }); 
	pObj->SetScale(Vec2{ 45.f,100.f }); 
	pObj->AllocComp(); 
	Camera::GetInst()->SetTarget(pObj); 
	AddObject(pObj, GROUP_TYPE::PLAYER);  

	//Clone ���� �ּ�ó�� 
	// 
	//shared_ptr<CObject> cObj = pObj->Clone();
 	//cObj->SetPos(Vec2{ 740.f,374.f });
 	//cObj->Init();//��������� Init()
 	//AddObject(cObj, GROUP_TYPE::PLAYER);

	Vec2 vResolution = Core::GetInst()->GetResolution();//���� ������
	float term= (vResolution.x - 75.f * 2) /(float )10.f;
	
	for (int i = 1; i < 3; i++)
	{
		shared_ptr<Monster> pMonsterObj = make_shared<Monster>(); 
		pMonsterObj->SetPos(Vec2( 50.f+i*term , 50.f));     
		pMonsterObj->SetScale(Vec2(60.f, 60.f)); 
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos()); 
		pMonsterObj->AllocComp();
		pMonsterObj->SetName(L"Monster");
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER); 
	}
	//�浹 ���� üũ
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);

	Camera::GetInst()->SetLookAt(vResolution/2.f);
}

void CSceneStart::Exit()
{
	DeleteAll();  
	CollisionMgr::GetInst()->Reset(); 
	Camera::GetInst()->SetTarget(nullptr);
}

CSceneStart::CSceneStart() 
{

}

CSceneStart::~CSceneStart()  
{

}
