#pragma once
#include "CObject.h"
#include "CKeyMgr.h"

class Texture;
enum class PLAYER_STATE {
	PLAYER_DASH_RIGHT,
	PLAYER_DASH_LEFT,
	PLAYER_STAND_RIGHT,
	PLAYER_STAND_LEFT,
	PLAYER_WALKING_LEFT,
	PLAYER_WALKING_RIGHT,
	END,
};
class Player : public CObject
{
private:
	shared_ptr<Texture> pTex;
	shared_ptr<Texture> pLeftTex;
	double mfDuration; // Dash �ð� ����
	double mfAccTime; //Dash ��� �ð�
	double mPacketTime;//packet ���� �ð�
	double mfPacketDuration;// packet ���� �ð� ����
	PLAYER_STATE pState;
	bool mDashCheck; // dash check 
public:

	KEY mCurKey;//dash key üũ

public:
	virtual void Update();
	virtual void Render(HDC hdc);
public:
	void CreateMissile();
public:
	Player();
	~Player();
	Player(const shared_ptr<CObject> origin):CObject(origin)
	{ 
		shared_ptr<Player> pObj = static_pointer_cast<Player>(origin);
		pTex = pObj->pTex;
		pLeftTex = pObj->pLeftTex;
		mfDuration = pObj->mfDuration;
		pState = PLAYER_STATE::PLAYER_STAND_RIGHT;
		mDashCheck = false;
	}
public:
	void AllocComp();
	virtual shared_ptr<CObject> Clone() 
	{ 
		shared_ptr<Player> pObj= make_shared<Player>(shared_from_this());
		pObj->Init();
		return pObj;
	}
};

