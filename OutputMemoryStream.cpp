#include "OutputMemoryStream.hpp"
#include "ByteSwap.hpp"

void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
	this->mBuffer = static_cast<char*>(std::realloc(this->mBuffer, inNewLength));
	// realloc 호출이 실패한 경우 처리
	// ...
	this->mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void* inData, size_t inByteCount)
{
	// 공간을 일단 충분히 확보
	uint32_t resultHead = this->mHead + static_cast<uint32_t>(inByteCount);
	if (resultHead > this->mCapacity)
		ReallocBuffer(std::max(this->mCapacity * 2, resultHead));

	// 버퍼의 제일 앞에 복사
	std::memcpy(this->mBuffer + this->mHead, inData, inByteCount);
	// mHead를 진전시켜 다음 기록에 대비
	this->mHead = resultHead;
}

template<typename T>
void OutputMemoryStream::Write(const T& inData)
{
	// 원시 자료형인지 여부를 컴파일 타임에 검사
	static_assert(
		std::is_arithemic<T>::value ||
		std::is_enum<T>::value,
		"Generic Write only supports primitive data types");
	
	if (STREAM_ENDIANNES == PLATFORM_ENDIANESS)
		Write(&inData, sizeof(inData));
	else
	{
		T swappedData = ByteSwap(inData);
		Write(&swappedData, sizeof(swappedData));
	}
}