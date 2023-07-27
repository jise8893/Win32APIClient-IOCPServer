#pragma once
struct Packet
{
public:
	Packet();
	virtual ~Packet();
	void Init();
public:
	int size;
	int id;

};
enum class PLAYER_STATE {
	PLAYER_DASH_RIGHT,
	PLAYER_DASH_LEFT,
	PLAYER_STAND_RIGHT,
	PLAYER_STAND_LEFT,
	PLAYER_WALKING_LEFT,
	PLAYER_WALKING_RIGHT,
	END,
};
struct GetSocketNumPacket : public Packet
{
public:
	void Init(SOCKET socket);
public:
	SOCKET socketId;

};

struct MoveToPacket :public Packet
{
public:
	void Init(int socketid);
public:
	int socketId;
	Vec2 pos;
	PLAYER_STATE pState;

};