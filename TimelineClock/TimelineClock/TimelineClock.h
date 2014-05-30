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
	 ���㲢��ȡ����һ֡�ļ��ʱ��
	 @return	���ؼ��ʱ�䣬��λ���롣�������������Ϊ(1/fps)����ͣ�򷵻�0
	 */
	float64 Step();

	float32	GetScale(){ return m_fScale; }
	void	SetScale(float32 value);

	int32	GetFPS(){ return m_framesPerSecond; }
	void	SetFPS(int32 value);

	float64	GetInterval(){ return m_frameInterval; }

	bool	IsPause(){ return m_bIsPause; }

private:
	float64		m_cyclesPerSecond;	// CPUÿ���ھ�����ʱ�䣬��λ��
	int32		m_framesPerSecond;	// ֡��fps
	float64		m_frameInterval;	// ÿ֡ʱ�䣬��λ��

	uint64		m_nCycles;			// CPUʱ�Ӿ���������
	float32		m_fScale;			// ���ţ�ʱ�������
	bool		m_bIsPause;			// �Ƿ���ͣ

	bool		m_bIsInit;			// �Ƿ��ʼ��
};

#endif