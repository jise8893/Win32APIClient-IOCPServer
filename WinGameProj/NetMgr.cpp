#include "pch.h"
#include "NetMgr.h"
#include "Packet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "OtherPlayer.h"
void NetMgr::RegisterRecvEvent()
{

    
    WSABUF wsaBuf;
    wsaBuf.buf = (char*)mRecvBuffer.GetWritePos(); 
    wsaBuf.len = mRecvBuffer.GetFreeSize();
    
    DWORD numOfBytes = 0;
    DWORD flags = 0;
    if (SOCKET_ERROR == ::WSARecv(clientSocket, &wsaBuf, 1, &numOfBytes, &flags, &mRecvEvent, nullptr)) 
    {
        int errCode = ::WSAGetLastError();
        if (errCode != WSA_IO_PENDING)
        {
            //disconnect 등록
            WSARecv(clientSocket, &wsaBuf, 1, &numOfBytes, &flags, &mRecvEvent, nullptr);
        }
    } 
}
void NetMgr::ProcessRecvEvent(DWORD numOfBytes)
{
    mRecvBuffer.OnWrite(numOfBytes);
    int processLen = ProcessData(mRecvBuffer.GetReadPos(), numOfBytes);
    mRecvBuffer.OnRead(processLen);
}
int NetMgr::ProcessData(BYTE* byte, int numOfBytes)
{
    int processedLen = 0;

    while (true)
    {
        int dataSize = numOfBytes - processedLen;

        if (dataSize < sizeof(Packet))
            break;

        Packet header = *(reinterpret_cast<Packet*>(&byte[0]));
        if (dataSize < header.size)
            break;
        TranslatePacket(&byte[processedLen], header.size);
        processedLen += header.size;

    }
    return processedLen;
}
void NetMgr::TranslatePacket(BYTE* buffer, int len)
{
    Packet* header = (Packet*)buffer;
    int PacketId = header->id;
    switch (PacketId)
    {
        case 2://GetSocketNumPacketId
        {
            GetSocketNumPacket* packet;
            packet =(GetSocketNumPacket*) header;
            myId = packet->socketId;

        }
            break;
        case 3://GetMoveToPacket
        {
            EditUserData( buffer,  len);
        }
            break;
    }
}

void NetMgr::SendMoveToPacket(MoveToPacket header)
{

    
    WSABUF wsaBuf; 
    wsaBuf.buf = (char*)&header; 
    wsaBuf.len = header.size; 
    DWORD numOfBytes = 0; 
    mSendEvent.Init();
    if (WSASend(clientSocket, &wsaBuf, 1, &numOfBytes, 0, &mSendEvent, nullptr) == SOCKET_ERROR) 
    {  
        int errCode = WSAGetLastError();
        if (errCode != WSA_IO_PENDING)
        { 
            WSASend(clientSocket, &wsaBuf, 1, &numOfBytes, 0, &mSendEvent, nullptr); 

        }
    }
}

void NetMgr::EditUserData(BYTE* buffer, int len) 
{
    lock_guard<std::mutex> lockGuard(mutex); 
    MoveToPacket* packet = (MoveToPacket*)buffer;
    userData userData;
    userData.pos = packet->pos;
    userData.pState = (int)packet->pState;
    //map 없으면 otherplayer 씬 추가
    if (mMapOthers.end() == mMapOthers.find(packet->socketId))
    {
        shared_ptr<OtherPlayer> pOtherPlayer = make_shared<OtherPlayer>(packet->socketId);
        pOtherPlayer->AllocComp();
        shared_ptr<Scene> pScene = SceneMgr::GetInst()->GetCurScene();
        if (pScene == nullptr)
        {
            return;
        }
        SceneMgr::GetInst()->GetCurScene()->AddObject(pOtherPlayer, GROUP_TYPE::OTHER_PLAYER);
    }

    mMapOthers[packet->socketId] = userData;
    return;
}

userData NetMgr::GetUserData(int socketId)
{
    lock_guard<std::mutex> lockGuard(mutex);
    return mMapOthers[socketId];
}

void NetMgr::Init()
{
    mRecvBuffer.Init(); 

    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
    {
        printf("Error - Can not load 'winsock.dll' file\n");
        return;
    }
    clientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED); 
    if (clientSocket == INVALID_SOCKET)
    {
        printf("Error - Invalid socket\n");
        return ;
    }

    IocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
    
    CreateIoCompletionPort((HANDLE)clientSocket, IocpHandle, 0, 0);

    memset(&serverAddr, 0, sizeof(SOCKADDR_IN));  
    serverAddr.sin_family = AF_INET;  
    serverAddr.sin_port = htons(8000);   
    inet_pton(AF_INET, "192.168.1.138", &serverAddr.sin_addr); 
    
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Error - Fail to connect\n");
        // 4. 소켓종료
        closesocket(clientSocket);
        // Winsock End
        WSACleanup();
        return ;
    }


    mSendEvent.Init(); 

    Packet header;
    header.Init();

    


    WSABUF wsaBuf;
    wsaBuf.buf = (char*) & header;
    wsaBuf.len = header.size;
    DWORD numOfBytes = 0;
    
    if (WSASend(clientSocket, &wsaBuf, 1, &numOfBytes, 0, &mSendEvent, nullptr) == SOCKET_ERROR)
    {
        int errCode = WSAGetLastError();
        if (errCode != WSA_IO_PENDING)
        {
            WSASend(clientSocket, &wsaBuf, 1, &numOfBytes, 0, &mSendEvent, nullptr);

        }
    }
    

    



}
void NetMgr::DisPatch()
{
    DWORD numOfBytes = 0; 
    ULONG_PTR key = 0; 
    OVERLAPPED* overlapped = nullptr; 
    IocpEvent* piocpEvent = nullptr; 
    if (GetQueuedCompletionStatus(IocpHandle, &numOfBytes, &key, reinterpret_cast<LPOVERLAPPED*>(&overlapped), 0))
    {
        piocpEvent = (IocpEvent*)overlapped;
        piocpEvent->DisPatch(numOfBytes);
    }

}
NetMgr::NetMgr()
{
 
}
NetMgr::~NetMgr()
{
    for (int i = 0; i < vPacket.size(); i++)
    {
        if (vPacket[i] != nullptr)
        {
            delete vPacket[i];
        }
    }
}
