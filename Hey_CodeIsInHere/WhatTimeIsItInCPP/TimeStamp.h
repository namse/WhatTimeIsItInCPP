#pragma once
#include "Time.h"
#include <chrono>
#include <ctime>
#include <time.h>
#include <Windows.h>
class TimeStamp
{
public:
	TimeStamp();
	~TimeStamp();

	void StartTimer();
	// because windows use function name - "GetCurrentTime", 
	// i name this function as joke. plz rename on your project as you want.
	Time WhatTimeIsIt(); 

private:
	std::chrono::microseconds m_StandardTime;
	LARGE_INTEGER m_StandardPerformanceCount;
	LARGE_INTEGER m_Frequency;
	
	
};


// CAUTION : QueryPerformanceCounter would be depended on CPU Core.
// It has some possibility that could return different value in same time on different threads.

// Global Instance For Multi- Thread Program.
// Make Instance Once and must call Initialization( StartTimer() )
extern TimeStamp* GTimeStamp;