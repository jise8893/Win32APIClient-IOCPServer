// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <WinSock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"mswsock.lib") 

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include <vector>
#include <memory>
#include <string>
#include "define.h"
#include "struct.h"
#include <math.h>
#include <map>
#include <atomic>
#include <mutex>
#pragma comment(lib,"Msimg32.lib")
using namespace std;
