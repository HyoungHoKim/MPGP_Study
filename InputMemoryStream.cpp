#include "InputMemoryStream.hpp"

void InputMemoryStream::Read(void* outData, uint32_t inByteCount)
{
	// 남은 데이터가 변환할 데이터의 크기보다 작다면 에러
	if (inByteCount > this->mCapacity - this->mHead)
	{
		std::cerr << "Cannot Read Data!!!" << std::endl;
		exit(1);
	}

	// 메모리 복사
	memcpy(outdata, this->mBuffer + this->head, inByteCount);
	// 읽어온 만큼 헤드 위치 이동
	this->head += inByteCount;
}