#include "RoboCat.hpp"

void RoboCat::Write(OutputMemoryStream& inStream) const
{
	inStream.Write(this->mHealth);
	inStream.Write(this->nMeowCount);
	// TODO: mHomeBase : 아직 처리 불가
	inStream.Write(this->mName, 128);
	// TODO: mMiceIndices : 아직 처리 불가
}

void RoboCat::Read(InputMemoryStream& inStream)
{
	inStream.Read(this->mHealth);
	inStream.Read(this->mMeowCount);
	// TODO: mHomeBase : 아직 처리 불가
	inStream.Read(this->nName, 128);
	// TODO: mMiceIndices : 아직 처리 불가
}

void SendRoboCat(int inSocket, const Robocat* inRoboCat)
{
	OutputMemoryStream stream;
	inRoboCat->Write(stream);
	send(inSocket, stream.GetBufferPtr(), stream.GetLength(), 0);
}

const uint32_t kMaxPacketSize = 1470;

void ReceiveRoboCat(int inSocket, RoboCat* outRoboCat)
{
	char* temporaryBuffer = static_cast<char*>(std::malloc(kMaxPacketSize));
	size_t receiveByteCount = recv(inSocket, temporaryBuffer, kMaxPacketSize, 0);

	if (receiveByteCount > 0)
	{
		InputMemoryStream stream(temporaryBuffer,
			static_cast<uint32_t>(receiveByteCount));
		outRoboCat->Read(stream);
	}
	else std::free(temporaryBuffer);
}