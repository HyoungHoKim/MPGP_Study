#ifndef MEMORYBITSTREAM_HPP
#define MEMORYBITSTREAM_HPP

class OutputBitMemoryStream
{
private:
	void ReallocBuffer(uint32_t inNewBitCapacity);

	char* mBuffer;
	uint32_t mBitHead;
	uint32_t mBitCapacity;

public:
	OutputBitMemoryStream() {
		ReallocBuffer(256);
	}
	~OutputBitMemoryStream() {
		std::free(mBuffer);
	}

	void WriteBits(uint8_t inData, size_t inBitCount);
	void WriteBits(const void* inData, size_t inBitCount);

	const char* GetBufferPtr() const {
		return (mBuffer);
	}
	const char* GetBitLength() const {
		return (mBitHead);
	}
	const char* GetByteLength() const {
		return ((mBitHead + 7) >> 3);
	}

	void WriteBytes(const void* inData, size_t inByteCount) {
		WriteBits(inData, inByteCount << 3);
	}
};


#endif