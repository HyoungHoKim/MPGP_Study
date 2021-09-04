#ifndef OUTPUTMEMORYSTREAM_HPP
#define OUTPUTMEMORYSTREAM_HPP

class OutputMemoryStream
{
private:
	void ReallocBuffer(uint32_t inNewLength);

	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;

public:
	OutputMemoryStream()
	: mBuffer(nullptr), mHead(0), mCapacity(0) {
		ReallocBuffer(32);
	}

	~OutputMemoryStream() {
		std::free(mBuffer);
	}

	// 스트림의 데이터 시작 위치 포인터를 구함
	const char* GetBufferPtr() const {
		return (mBuffer);
	}

	uint32_t GetLength() const {
		return (mHead);
	}

	void Write(const void* inData, int inByteCount);
	template<typename T> void Write(const T& inData);
	
	/*
	void Write(uint32_t inData) {
		Write(&inData, sizeof(inData));
	}
	void Write(int32_t inData) {
		Write(&inData, sizeof(inData));
	}
	*/
};



#endif