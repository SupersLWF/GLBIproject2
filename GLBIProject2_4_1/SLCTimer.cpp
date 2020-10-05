#include "SLCTimer.h"

SLCTimer::SLCTimer()
{
}

SLCTimer::SLCTimer(time_t* start)
{
	time(start);
}

void SLCTimer::Start()
{
	time(&start);
}

void SLCTimer::getDiffTime()
{
	time(&end);
	cost = difftime(start,end);
}
