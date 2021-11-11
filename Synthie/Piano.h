#pragma once
#include "Instrument.h"
#include "PianoWave.h"
#include "AR.h"
#include <string>

using namespace std;

class CPiano :
    public CInstrument
{
public:
	CPiano();
	CPiano(double bpm);
	virtual ~CPiano();
public:
	const double NUM_SECS_IN_MINUTE = 60.0;
	virtual void Start();
	virtual bool Generate();

	void SetFreq(double f) { m_pianowave.SetFreq(f); }
	void SetAmplitude(double a) { m_pianowave.SetAmplitude(a); }
	void SetDuration(double d) { m_duration = d; }
	virtual void SetNote(CNote* note);
private:
	CPianoWave   m_pianowave;
	double m_duration;
	double m_time;
	double m_attack;
	double m_decay;
	double m_sustain;
	double m_release;
	string m_envelope;
	double m_stop_amp;
	double m_stop_time;
	bool m_pedal;
};


