#include "TimeStamp.h"

TimeStamp* GTimeStamp = nullptr;

TimeStamp::TimeStamp()
{
}


TimeStamp::~TimeStamp()
{
}

void TimeStamp::StartTimer()
{
	auto now = std::chrono::system_clock::now();
	m_StandardTime = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
	
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_StandardPerformanceCount);
}

Time TimeStamp::WhatTimeIsIt()
{ 
	LARGE_INTEGER currentPerformanceCount, elapsedMicroseconds;
	QueryPerformanceCounter(&currentPerformanceCount);

	elapsedMicroseconds.QuadPart = currentPerformanceCount.QuadPart - m_StandardPerformanceCount.QuadPart;
	
	// We now have the elapsed number of ticks, along with the
	// number of ticks-per-second. We use these values
	// to convert to the number of elapsed microseconds.
	// To guard against loss-of-precision, we convert
	// to microseconds *before* dividing by ticks-per-second.
	
	elapsedMicroseconds.QuadPart *= 1000000;
	elapsedMicroseconds.QuadPart /= m_Frequency.QuadPart;

	auto currentTime = m_StandardTime.count() + elapsedMicroseconds.QuadPart;

	Time ret;
	ret.micro = currentTime % 1000;
	ret.milli = (currentTime / 1000) % 1000;
	
	std::time_t t = (time_t)(currentTime / 1000000);
	std::tm * tm = std::localtime(&t);
	
	// Make Sure.. It is 21' Century!
	ret.year = tm->tm_year - 100;
	ret.month = tm->tm_mon + 1;
	ret.day = tm->tm_mday + 1;
	ret.hour = tm->tm_hour;
	ret.minute = tm->tm_min;
	ret.second = tm->tm_sec;

	return ret;
}