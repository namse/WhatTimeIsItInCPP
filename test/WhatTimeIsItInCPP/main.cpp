
#include "Time.h"
#include "TimeStamp.h"
int main(int argc, char* argv[])
{
	GTimeStamp = new TimeStamp();
	GTimeStamp->StartTimer();



	Time time1 = GTimeStamp->WhatTimeIsIt();

	int a = 0;
	for (int i = 0; i < 1; i++)
	{
		a++;
	}


	Time time2 = GTimeStamp->WhatTimeIsIt();
	Time time3 = GTimeStamp->WhatTimeIsIt();

	return 0;
}

