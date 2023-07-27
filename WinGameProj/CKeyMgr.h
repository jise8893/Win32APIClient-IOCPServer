#pragma once
enum class KEYSTATE {
	TAP, //눌리지 않고 이전에도 눌리지 않음
	HOLD, // 막 누름
	AWAY, // 누루고 있음
	NONE, //막 뗀 시점
};
enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	LBTN,
	RBTN,
	LAST,
};
struct tKeyInfo
{
	KEYSTATE	eState;
	KEYSTATE	ePrevState;
	bool		bPrev; //이전 프레임에서 눌렸는지 여부
};
class CKeyMgr
{
	SINGLE(CKeyMgr) 
public:
	void Init();
	void Update();
	
private:
	std::vector<tKeyInfo> mVecKey;
	Vec2 mCurMousePos;
public:
	KEYSTATE GetKeyState(KEY key);
	KEYSTATE GetPrevKeyState(KEY key);
	Vec2 GetMousePos();

};

