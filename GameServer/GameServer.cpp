
#include "pch.h"
#include "ServerCore.h"
#include "ThreadMgr.h"
int main()
{
	shared_ptr<ServerCore> pServerCore = make_shared<ServerCore>();
	pServerCore->Start();

	for (int i = 0; i < 7; i++)
	{
		ThreadMgr::GetInst()->Launch([=]() {
			while (true)
			{
				pServerCore->DisPatch();
			}
			
			}
		);
	}

	ThreadMgr::GetInst()->Join();
}
