#include "TimeStamp.h"

TimeStamp* GTimeStamp = nullptr;


void TimeStamp::StartTimer()
{
	auto now = std::chrono::system_clock::now();
	m_StandardTime = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch())
		+ std::chrono::hours(m_UTC);
	
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_StandardPerformanceCount);

	SetDefaultDay();
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

	ret.second = t % 60;
	ret.minute = (t / 60) % 60;
	ret.hour = (t / 3600) % 24 + m_UTC;
	if (m_StandardEpochDay != t / (3600 * 24))
		UpdateDefaultDay(t / (3600 * 24));
	ret.day = m_StandardDay;
	ret.month = m_StandardMonth;
	ret.year = m_StandardYear;

	return ret;
}
#include <iostream>
void TimeStamp::SetDefaultDay()
{
	std::time_t t = (time_t)(m_StandardTime.count() / 1000000);
	std::tm* tm = std::gmtime(&t);
	
	
	m_StandardYear = tm->tm_year + 1900;
	m_StandardMonth = tm->tm_mon + 1;
	m_StandardDay = tm->tm_mday;
	m_StandardEpochDay = ((t / 3600) + m_UTC) / 24;
	m_StandardGDay = GetGDay(tm->tm_year, tm->tm_mon + 1, tm->tm_mday) - m_StandardEpochDay;
}

void TimeStamp::UpdateDefaultDay(int dayFromEpoch)
{
	GetDate(m_StandardGDay + dayFromEpoch,
		m_StandardYear,
		m_StandardMonth,
		m_StandardDay);
	if (IS_21_CENTURY)
		m_StandardYear -= 100;

	m_StandardEpochDay = dayFromEpoch;
}

int TimeStamp::GetGDay(int year, int month, int day)
{
	int y = year;
	int m = month;
	int d = day;
	m = (m + 9) % 12;
	y = y - m / 10;
	return 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1);
}

void TimeStamp::GetDate(IN int GDay, OUT int& year, OUT int& month, OUT int& day)
{
	int y = (10000 * GDay + 14780) / 3652425;
	int ddd = GDay - (365 * y + y / 4 - y / 100 + y / 400);
	if (ddd < 0)
	{
		y = y - 1;
		ddd = GDay - (365 * y + y / 4 - y / 100 + y / 400);
	}
	int mi = (100 * ddd + 52) / 3060;

	// return
	month = (mi + 2) % 12 + 1;
	year = y + (mi + 2) / 12 + 1900;
	day = ddd - (mi * 306 + 5) / 10 + 1;
}
