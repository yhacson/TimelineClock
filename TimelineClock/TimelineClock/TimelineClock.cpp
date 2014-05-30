#include "TimelineClock.h"

#include <Windows.h>

TimelineClock::TimelineClock()
	:m_framesPerSecond(60), m_fScale(1.0f), m_frameInterval(1.0f/60), m_bIsPause(true), m_bIsInit(false)
{
}

TimelineClock::~TimelineClock()
{}

bool TimelineClock::Init(int32 framePerSecond)
{
	this->SetFPS(framePerSecond);

	LARGE_INTEGER nFreq;
	if(!QueryPerformanceFrequency(&nFreq))
	{
		Log("不支持高精度计时器！");
		return false;
	}
	m_cyclesPerSecond = nFreq.QuadPart;

	m_bIsInit = true;
	return true;
}

void TimelineClock::Start()
{
	if(!m_bIsInit)
	{
		Log("Clock未初始化！");
		return;
	}
	
	LARGE_INTEGER nStart;
	QueryPerformanceCounter(&nStart);
	m_nCycles = nStart.QuadPart;

	m_bIsPause = false;
}

float64 TimelineClock::Step()
{
	if(m_bIsPause){
		return 0;
	}

	LARGE_INTEGER nNow;
	QueryPerformanceCounter(&nNow);
	float64 dt = (nNow.QuadPart - m_nCycles) / m_cyclesPerSecond;

	if(m_fScale != 0){
		dt = dt * m_fScale;
	}
	if(dt >= m_frameInterval)
	{
		m_nCycles = nNow.QuadPart;
		// 防止dt过大
		dt = m_frameInterval;
	}

	return dt;
}

void TimelineClock::SetScale(float32 value)
{
	m_fScale = value;
}

void TimelineClock::SetFPS(int32 value)
{
	m_framesPerSecond = value; 
	m_frameInterval = 1.0f / m_framesPerSecond;
}