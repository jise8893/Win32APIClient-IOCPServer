#pragma once
#include <vector>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <memory>
#include <MSWSock.h>
#include <atomic>
#include <mutex>
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"mswsock.lib") 
using namespace std;
#include <thread>
#include "struct.h"

template<typename T>
inline bool SetSockOpt(SOCKET socket, int level, int optName, T optVal);

bool SetUpdateAcceptSocket(SOCKET socket, SOCKET listenSocket);
bool SetReuseAddress(SOCKET socket, bool flag);
bool SetLinger(SOCKET socket, int onoff, int linger);  