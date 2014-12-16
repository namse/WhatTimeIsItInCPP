#pragma once
#include "Time.h"
#include <chrono>
#include <ctime>
#include <time.h>
#include <Windows.h>

#define IS_21_CENTURY true

class TimeStamp
{
public:
	TimeStamp(int UTC = +9) : m_UTC(UTC)
	{};
	~TimeStamp()
	{};

	// default setting is Seoul.
	void StartTimer();
	// because windows use function name - "GetCurrentTime", 
	// i name this function as joke. plz rename on your project as you want.
	Time WhatTimeIsIt();

private:
	// We Should Calculate Y/M/D First.
	// Because that calculation is too heavy.
	void SetDefaultDay();
	void UpdateDefaultDay(int dayFromEpoch);

	// Algorithm from http://alcor.concordia.ca/~gpkatch/gdate-algorithm.html
	int GetGDay(int year, int month, int day);
	void GetDate(IN int GDay, OUT int& year, OUT int& month, OUT int& day);
private:
	std::chrono::microseconds m_StandardTime;
	LARGE_INTEGER m_StandardPerformanceCount;
	LARGE_INTEGER m_Frequency;

	int m_UTC;
	int m_StandardYear;
	int m_StandardMonth;
	int m_StandardDay;
	int m_StandardEpochDay;
	int m_StandardGDay;
};


// CAUTION : QueryPerformanceCounter would be depended on CPU Core.
// It has some possibility that could return different value in same time on different threads.

// Global Instance For Multi- Thread Program.
// Make Instance Once and must call Initialization( StartTimer() )
extern TimeStamp* GTimeStamp;