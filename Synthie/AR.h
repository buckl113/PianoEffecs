#pragma once
#include "AudioNode.h"
class CAR :
	public CAudioNode
{
public:
	CAR();
	~CAR();
private:
	double m_duration;
	double m_time;
	double m_attack;
	double m_release;
	double m_reverb;
	bool m_flanging;
	CAudioNode* m_source;
public:
	void SetSource(CAudioNode* const &source) { m_source = source; }
	void SetDuration(double d) { m_duration = d; }
	void SetReverb(double r) { m_reverb = r; }
	void SetFlanging(bool f) { m_flanging = f; }
	double GetTime() { return m_time; }
	virtual void Start();
	virtual bool Generate();
};

