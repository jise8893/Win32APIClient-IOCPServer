#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer() :mBuffer{}, mBufferSize(500), mCapacity(1024), mReadPos(0), mWritePos(0)
{
	mBuffer.resize(mCapacity);
}

RecvBuffer::~RecvBuffer()
{

}

void RecvBuffer::Init()
{
	mBuffer.resize(mCapacity);
	mBufferSize = 500;
	mCapacity = 1024;
	mReadPos = 0;
	mWritePos = 0;
}

int RecvBuffer::OnRead(int numOfBytes)
{
	mReadPos += numOfBytes;
	Clean();
	return 0;
}

void RecvBuffer::Clean()
{
	int dataSize = GetDataSize();
	if (dataSize == 0)
	{
		mReadPos = 0;
		mWritePos = 0;
	}
	else {
		if (GetFreeSize() < mBufferSize)
		{
			memcpy(&mBuffer[0], &mBuffer[mReadPos], dataSize);
			mReadPos = 0;
			mWritePos = dataSize;
		}
	}


}





