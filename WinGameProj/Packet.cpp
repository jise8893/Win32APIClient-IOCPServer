#include "pch.h"
#include "Packet.h"

Packet::Packet() :size(sizeof(Packet)), id(0)
{
}

Packet::~Packet()
{
}

void Packet::Init()
{
	size = sizeof(Packet);
	id = 1;
}

void GetSocketNumPacket::Init(SOCKET socket)
{

	size = sizeof(GetSocketNumPacket);
	id = 2;
	socketId = socket;
}

void MoveToPacket::Init(int socketid)
{
	id = 3;
	size = sizeof(MoveToPacket);
	socketId = socketid;
	pos = Vec2(0.f, 0.f);
}
