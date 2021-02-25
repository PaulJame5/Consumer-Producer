#include "Consumer.h"
#include <iostream>

Consumer::Consumer(std::mutex* sharedLock)
{
	this->sharedLock = sharedLock;
	myId = nextId;
}

Consumer::~Consumer()
{
}

void Consumer::consumeData(int data, int pos) 
{
	std::cout << "ID: " << myId << ", consumed burger number: " << data << " at buffer pos: " << pos << "\n";

}

// consumer thread function
void Consumer::consumer() {

	while (true)
	{
		if (Globals::availableSlots >= Globals::MAX_BUFFER_SIZE)
		{
			std::cout << "spinning consumer" << "\n";
			continue;
		}
		sharedLock->lock();
		if (Globals::dataBuffer[Globals::front] == -1)
		{
			std::cout << "soeone already ate it" << "\n";
			sharedLock->unlock();
			continue;
		}

		consumeData(Globals::dataBuffer[Globals::front], Globals::front); 
		Globals::dataBuffer[Globals::front] = -1;
		Globals::front = (Globals::front + 1) % Globals::MAX_BUFFER_SIZE;
		Globals::availableSlots++;
		sharedLock->unlock();
	}
}
int Consumer::nextId = 0;

