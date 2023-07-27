#include "pch.h"
#include "Tile.h"

void Tile::Render(HDC hdc)
{
	if (pTileTex == nullptr)
		return;

	Vec2 vRenderPos = GetPos();
	Vec2 vScale = GetScale();
	Vec2 vFinalPos=Camera::GetInst()->GetRenderPos(vRenderPos);

	Rectangle(hdc, vFinalPos.x, vFinalPos.y, vFinalPos.x+ vScale.x , vFinalPos.y + vScale.y);
}

void Tile::Update()
{
}

Tile::~Tile()
{
	pTileTex = nullptr;
}

Tile::Tile() :pTileTex(nullptr)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}
