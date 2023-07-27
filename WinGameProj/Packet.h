#pragma once
#include "Player.h"
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