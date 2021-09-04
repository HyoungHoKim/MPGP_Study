#include "MemoryBitStream.hpp"

void OutputBitMemoryStream::WriteBits(uint8_t, size_t inBitCount)
{
	uint32_t nextBitHead = mBitHead + static_cast<uint32_t>(inBitCount);
	if (nextBitHead > mBitCapacity)
		ReallocBuffer(std::max(mBitCapacity * 2, nextBitHead));

	// 바이트 오프셋: 비트 헤드를 8로 나눔
	// 비트 오프셋: 8에 대한 나머지
	uint32_t byteOffset = mBitHead >> 3;
	uint32_t bitOffset = mBitHead & 0x7;

	// 현재 처리 중 바이트에서 몇 비트를 남길지 계산
	uint8_t currentMask = ~(0xff << bifOffset);
	mBuffer[byteOffset] = (mBuffer[byteOffset] & currentMask) | (inData << bitOffset);

	// 기록할 바이트에 몇 비트가 아직 남아있나 계산
	uint32_t bitsFreeThisByte = 8 - bitOffset;

	// 공간이 모자라면 다음 바이트에 넘김
	if (bitsFreeThisByte < inBitCount){
		mBuffer[byteOffset + 1] = inData >> bitsFreeThisByte;
	}

	mBitHead = nextBitHead;
}

void OutputBitMemoryStream::WriteBits(const void* Data, size_t inBitCount)
{
	const char* srcByte = static_cast<const char*>(inData);

	// 바이트를 하나씩 모두 기록
	while (inBitCount > 8)
	{
		WriteBits(*srcByte, 8);
		++srcByte;
		inBitCount -= 8;
	}

	// 아직 남은 비트를 기록
	if (inBitCount > 0)
		WriteBits(*srcByte, inBitCount);
}