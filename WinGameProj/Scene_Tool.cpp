#include "pch.h"
#include "Scene_Tool.h"
#include "func.h"
#include "CKeyMgr.h"
#include "CollisionMgr.h"
#include "Tile.h" 
#include "Core.h"
#include "ResMgr.h"
void Scene_Tool::Enter()
{
	shared_ptr<Texture> pTex = ResMgr::GetInst()->LoadTexture(L"Map1", L"Texture\\Tile\\Map1.bmp");

	Vec2 vResolution = Core::GetInst()->GetResolution();
	Vec2 vRenderPos = Camera::GetInst()->GetRenderPos(vResolution); 
	//타일생성
	for (int i = 0; i < 5; i++)
	{ 
		for (int j = 0; j < 5; j++)
		{
			shared_ptr<Tile> pTile = make_shared<Tile>();
			pTile->SetTexture(pTex);
			pTile->SetPos(Vec2(vRenderPos.x/2.f +float(TILE_SIZE * j), vRenderPos.y/2.f+float(i * TILE_SIZE)));
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
	Camera::GetInst()->SetLookAt(vRenderPos);
}

void Scene_Tool::Exit()
{
	DeleteAll(); 
	CollisionMgr::GetInst()->Reset();  
} 

void Scene_Tool::Update() 
{ 
	Scene::Update(); 
	if (KEY_CHECK(KEY::ENTER, KEYSTATE::TAP))  
	{
		ChangeScene(SCENE_TYPE::START); 
	} 
}

Scene_Tool::Scene_Tool()
{
}

Scene_Tool::~Scene_Tool()
{
}
