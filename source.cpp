#include <chrono>
#include <cstdint>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <time.h>
int _tmain(int argc, _TCHAR* argv[])
{
	auto now = std::chrono::system_clock::now();
	std::chrono::microseconds microSecond
		= std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());

	struct Time{
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int second;
		int milli;
		int micro;
	}mTime;

	mTime.micro = microSecond.count() % 1000;
	mTime.milli = (microSecond.count()  / 1000) % 1000;

	std::time_t t = std::chrono::system_clock::to_time_t(now);
	std::tm * tm = std::localtime(&t);
	mTime.year = tm->tm_year - 100;
	mTime.month = tm->tm_mon + 1;
	mTime.day = tm->tm_mday + 1;
	mTime.hour = tm->tm_hour;
	mTime.minute = tm->tm_min;
	mTime.second = tm->tm_sec;


	return 0;
}

