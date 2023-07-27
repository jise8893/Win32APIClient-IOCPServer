#pragma once
class RecvBuffer
{
private:
	friend class Session;
public:
	vector<BYTE> mBuffer;
	UINT mBufferSize;
	INT mReadPos;
	INT mWritePos;
	INT mCapacity;
public:
	RecvBuffer();
	~RecvBuffer();
	void Init();
public:
	int OnRead(int numOfBytes);
	void OnWrite(DWORD number) {  mWritePos += number;  }
	void Clean();
public:
	//int ProcessData(BYTE* buffer, int len); 
	BYTE* GetWritePos() { return &mBuffer[mWritePos];}
	BYTE* GetReadPos() { return &mBuffer[mReadPos]; }
	int GetFreeSize() { return mCapacity - mWritePos; }
	int GetDataSize() { return mWritePos - mReadPos; }
};

