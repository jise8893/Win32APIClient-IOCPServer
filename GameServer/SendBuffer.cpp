#include "pch.h"
#include "SendBuffer.h"


SendBuffer::SendBuffer() 
{
	_buffer.resize(1024);
}

SendBuffer::~SendBuffer()
{

}
