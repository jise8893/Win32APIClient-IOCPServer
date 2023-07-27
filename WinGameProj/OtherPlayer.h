#pragma once
#include "CObject.h"
#include "CKeyMgr.h"
class Texture;

enum class OPLAYER_STATE {
	PLAYER_DASH_RIGHT,
	PLAYER_DASH_LEFT,
	PLAYER_STAND_RIGHT,
	PLAYER_STAND_LEFT,
	PLAYER_WALKING_LEFT,
	PLAYER_WALKING_RIGHT,
	END,
};

class OtherPlayer : public CObject
{
private:
	shared_ptr<Texture> pTex;
	shared_ptr<Texture> pLeftTex;
	double mfDuration; // Dash 시간 제한
	double mfAccTime; //Dash 계산 시간
	double mPacketTime;//packet 전송 시간
	double mfPacketDuration;// packet 전송 시간 제한
	OPLAYER_STATE pState;
	bool mDashCheck; // dash check 
public:

	KEY mCurKey;//dash key 체크
public:
	int socketId;
public:
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual shared_ptr<CObject> Clone();
public:
	OtherPlayer() = delete;
	OtherPlayer(int id);
	~OtherPlayer();

public:
	void AllocComp();

};

