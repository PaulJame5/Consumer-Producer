#include "Producer.h"
#include <iostream>

Producer::Producer(std::mutex * sharedLock)
{
	this->sharedLock = sharedLock;
	myId = nextId++;
}

Producer::~Producer()
{
}

int Producer::produceData(int pos) {
	static int burgerNumber = 0;

	std::cout << "ID: " << myId << ", produced burger number: " << burgerNumber << " at buffer pos: " << Globals::back << "\n";
	burgerNumber++;
	return burgerNumber;
}


void Producer::producer() {
	while (true) {

		if (Globals::availableSlots < 1)
		{
			std::cout << "spinning producer" << "\n";
			if (Globals::availableSlots < 0)
			{
				Globals::availableSlots = 0;
			}
			continue;
		}
		sharedLock->lock();
		Globals::dataBuffer[Globals::back] = produceData(Globals::back);
		Globals::back = (Globals::back + 1) % Globals::MAX_BUFFER_SIZE;
		Globals::availableSlots--;
		sharedLock->unlock();
	}
}
int Producer::nextId = 0;

