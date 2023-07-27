#pragma once
#include "CObject.h" 
class Texture;
class Tile: public CObject 
{
private:
	shared_ptr<Texture> pTileTex; 
private:
	virtual void Render(HDC hdc);
	virtual void Update();
public:
	Tile();
	~Tile();
	void SetTexture(shared_ptr<Texture> pTex) { pTileTex = pTex; }
	Tile(const shared_ptr<CObject> origin) :CObject(origin)
	{
		shared_ptr<Tile> pObj = static_pointer_cast<Tile>(origin);
		
	}
	virtual shared_ptr<CObject> Clone()
	{
		shared_ptr<Tile> pObj = make_shared<Tile>(shared_from_this()); 
		pObj->Init();
		return pObj;
	}
	
};

