#include "TimeLineClock.h"

#include <Windows.h>

TimeLineClock::TimeLineClock()
	:m_framesPerSecond(60), m_fScale(1.0f), m_frameInterval(1.0f/60), m_bIsPause(true), m_bIsInit(false)
{
}

TimeLineClock::~TimeLineClock()
{}

bool TimeLineClock::Init(int32 framePerSecond)
{
	this->SetFPS(framePerSecond);

	LARGE_INTEGER nFreq;
	if(!QueryPerformanceFrequency(&nFreq))
	{
		Log("��֧�ָ߾��ȼ�ʱ����");
		return false;
	}
	m_cyclesPerSecond = nFreq.QuadPart;

	m_bIsInit = true;
	return true;
}

void TimeLineClock::Start()
{
	if(!m_bIsInit)
	{
		Log("Clockδ��ʼ����");
		return;
	}
	
	LARGE_INTEGER nStart;
	QueryPerformanceCounter(&nStart);
	m_nCycles = nStart.QuadPart;

	m_bIsPause = false;
}

float64 TimeLineClock::Step()
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
		// ��ֹdt����
		dt = m_frameInterval;
	}

	return dt;
}

void TimeLineClock::SetScale(float32 value)
{
	m_fScale = value;
}

void TimeLineClock::SetFPS(int32 value)
{
	m_framesPerSecond = value; 
	m_frameInterval = 1.0f / m_framesPerSecond;
}