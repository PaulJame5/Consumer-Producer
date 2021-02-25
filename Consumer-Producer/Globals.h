#pragma once
#define Buffer_Limit 10
#include <mutex>
#include <queue>


class Globals
{
public:
	Globals();
	~Globals();
	static const int MAX_BUFFER_SIZE = 5;
	static int dataBuffer[];
	static int availableSlots;
	static int front, back;

	static void initDataBuffer();

private:

};