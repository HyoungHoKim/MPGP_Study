#ifndef ROBOCAT_HPP
#define ROBOCAT_HPP

#include "OutputMemoryStream.hpp" 

class RoboCat : public GameObject
{
private:
	int32_t					mHealth;
	int32_t					mMeowCount;
	GameObject*				mHomeBase;
	char					mName[128];
	std::vector<int32_t>	mMiceIndices;

public:
	RoboCat() : mHealth(10), mMeowCount(3), mHomeBase(0)
	{
		mName[0] = '\0';
	}

	virtual void Update();

	void Write(OutputMemoryStream& inStream) const;
	void Read(InputMemoryStream& inStream);

};

#endif