#pragma once
enum class KEYSTATE {
	TAP, //������ �ʰ� �������� ������ ����
	HOLD, // �� ����
	AWAY, // ����� ����
	NONE, //�� �� ����
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
	bool		bPrev; //���� �����ӿ��� ���ȴ��� ����
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

