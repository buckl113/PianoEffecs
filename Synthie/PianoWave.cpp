#include "stdafx.h"
#include "PianoWave.h"


CPianoWave::CPianoWave()
{
	m_phase = 0;
	m_amp = 0.1;
	m_freq = 440;
}


CPianoWave::~CPianoWave()
{
}

void CPianoWave::Start()
{
	m_phase = 0;
}

bool CPianoWave::Generate()
{
	// Source = https://dsp.stackexchange.com/questions/46598/mathematical-equation-for-the-sound-wave-that-a-piano-makes
	m_frame[0] = m_amp * (-1 / 4 * sin(3 * PI * m_phase) + 1 / 4 * sin(PI * m_phase) + sqrt(3) / 2 * cos(PI * m_phase));
	m_frame[1] = m_frame[0];

	m_phase += m_freq * GetSamplePeriod();

	return true;
}