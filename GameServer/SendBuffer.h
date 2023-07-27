#pragma once
#include <vector>
class SendBuffer : enable_shared_from_this<SendBuffer>
{
public:
	SendBuffer();
	~SendBuffer();

	BYTE* Buffer() { return _buffer.data(); }



private:
	vector<BYTE> _buffer;

};