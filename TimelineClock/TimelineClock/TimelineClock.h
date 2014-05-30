#ifndef _TIMELINECLOCK_H_
#define _TIMELINECLOCK_H_

#include "TypeDef.h"
#include "Log.h"

class TimelineClock
{
public:
	TimelineClock();
	~TimelineClock();

	bool Init(int32 framePerSecond = 60);
	void Start();
	void Pause(){ m_bIsPause = true; }

	/**
	 计算并获取与上一帧的间隔时间
	 @return	返回间隔时间，单位：秒。如果过大则锁定为(1/fps)，暂停则返回0
	 */
	float64 Step();

	float32	GetScale(){ return m_fScale; }
	void	SetScale(float32 value);

	int32	GetFPS(){ return m_framesPerSecond; }
	void	SetFPS(int32 value);

	float64	GetInterval(){ return m_frameInterval; }

	bool	IsPause(){ return m_bIsPause; }

private:
	float64		m_cyclesPerSecond;	// CPU每周期经过的时间，单位秒
	int32		m_framesPerSecond;	// 帧率fps
	float64		m_frameInterval;	// 每帧时间，单位秒

	uint64		m_nCycles;			// CPU时钟经过的周期
	float32		m_fScale;			// 缩放（时间快慢）
	bool		m_bIsPause;			// 是否暂停

	bool		m_bIsInit;			// 是否初始化
};

#endif