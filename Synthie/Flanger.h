#pragma once
#include "Instrument.h"
#include "SineWave.h"
#include "AR.h"
#include <vector>

using namespace std;

class CFlanger :
    public CInstrument
{
public:
	CFlanger();
	CFlanger(double bpm);
	virtual ~CFlanger();
public:
	const double NUM_SECS_IN_MINUTE = 60.0;
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_sinewave.SetFreq(f); }
	void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }
	void SetDuration(double d) { m_duration = d; }
	virtual void SetNote(CNote* note);
private:
	CSineWave   m_sinewave;
	CAR m_ar1;
	CAR m_ar2;
	bool m_start2;
	double m_duration;
	double m_time;
	vector<double> m_queue;
	int m_wrloc;
	int m_queuesize;
	double m_delay;
};
