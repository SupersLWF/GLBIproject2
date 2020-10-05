#pragma once
#include <process.h>
#include <time.h>


class SLCTimer
{
private:
	time_t start;
	time_t end;

	double cost;
public:
	SLCTimer();
	SLCTimer(time_t* start);

	void Start();
	void getDiffTime();
};

