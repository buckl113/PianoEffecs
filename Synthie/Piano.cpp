#include "stdafx.h"
#include "Piano.h"
#include "Notes.h"
#include <string>

using namespace std;

CPiano::CPiano()
{
	m_duration = 0.5;
	m_attack = 0.1;
	m_decay = .4;
	m_sustain = 5;
	m_release = 0.115;
	m_envelope = "attack";
	m_stop_amp = 0;
	m_stop_time = 0;
}

// Constructor to set the beats per minute
CPiano::CPiano(double bpm)
{
	m_duration = 0.5;
	m_bpm = bpm;
	m_attack = 0.1;
	m_decay = .3;
	m_sustain = 5;
	m_release = 0.115;
	m_envelope = "attack";
	m_stop_amp = 0;
	m_stop_time = 0;
}

CPiano::~CPiano()
{
}

void CPiano::Start()
{
	m_pianowave.SetSampleRate(GetSampleRate());
	m_pianowave.Start();
	m_time = 0;
}


bool CPiano::Generate()
{
	// Tell the component to generate an audio sample
	m_pianowave.Generate();

	// Read the component's sample and make it our resulting frame.
	/*if (m_time > m_attack + m_sustain) {
		m_envelope = "end";
		m_frame[0] = 0;
		m_frame[1] = 0;
	}
	else if (m_time > m_duration - m_release)
	{
		if (m_envelope == "decay") {
			m_stop_amp = (m_attack + m_decay - m_time) / (m_decay);
		}
		else if (m_envelope == "sustain") {
			m_stop_amp = (m_attack + m_sustain - m_time) / (m_sustain)/2;
		}
		else {
			m_stop_amp = m_time / m_attack;
		}
		m_stop_time = m_time;
		m_envelope = "release";
		m_frame[0] = m_pianowave.Frame(0) * m_stop_amp * (m_release - m_time + m_stop_time) / (m_release);
		m_frame[1] = m_pianowave.Frame(1) * m_stop_amp * (m_release - m_time + m_stop_time) / (m_release);
	}
	else if (m_time < m_attack)
	{
		m_frame[0] = m_pianowave.Frame(0) * m_time / m_attack;
		m_frame[1] = m_pianowave.Frame(1) * m_time / m_attack;
	}
	else if (m_time < m_attack + m_decay/2) {
		m_envelope = "decay";
		m_frame[0] = m_pianowave.Frame(0) * (m_attack + m_decay - m_time) / (m_decay);
		m_frame[1] = m_pianowave.Frame(1) * (m_attack + m_decay - m_time) / (m_decay);
	}
	else
	{
		m_envelope = "sustain";
		m_frame[0] = m_pianowave.Frame(0) * (m_attack + m_sustain - m_time) / (m_sustain) / 2;
		m_frame[1] = m_pianowave.Frame(1) * (m_attack + m_sustain - m_time) / (m_sustain) / 2;
	}*/
	if (m_duration < .2) {
		m_attack = .07;
	}
	if (m_duration < .5) {
		m_decay = 0;
		m_release = m_duration - m_attack;
	}
	if (m_time > m_duration - m_release)
	{
		if (m_time < m_attack + m_decay * 2 / 3) {
			bool whoops = TRUE;
		}
		if (m_decay == 0) {
			m_frame[0] = m_pianowave.Frame(0) * (m_duration - m_time) / (m_release);
			m_frame[1] = m_pianowave.Frame(1) * (m_duration - m_time) / (m_release);
		}
		else {
			m_frame[0] = m_pianowave.Frame(0) * (m_duration - m_time) / (m_release) / 3;
			m_frame[1] = m_pianowave.Frame(1) * (m_duration - m_time) / (m_release) / 3;
		}
	}
	else if (m_time < m_attack)
	{
		m_frame[0] = m_pianowave.Frame(0) * m_time / m_attack;
		m_frame[1] = m_pianowave.Frame(1) * m_time / m_attack;
	}
	else if (m_time < m_attack + m_decay *2 / 3) {
		m_envelope = "decay";
		m_frame[0] = m_pianowave.Frame(0) * (m_attack + m_decay - m_time) / (m_decay);
		m_frame[1] = m_pianowave.Frame(1) * (m_attack + m_decay - m_time) / (m_decay);
	}
	else
	{
		m_envelope = "sustain";
		m_frame[0] = m_pianowave.Frame(0) / 3;
		m_frame[1] = m_pianowave.Frame(1) / 3;
	}
	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration.
	return m_time < m_duration; 


	// Update time
	m_time += GetSamplePeriod();

	// We return true until the time reaches the duration returned by the AR object.
	return m_time < m_duration;
}

void CPiano::SetNote(CNote* note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			// SetDuration(value.dblVal); // play the note for the duration in terms of seconds
			SetDuration(value.dblVal * (NUM_SECS_IN_MINUTE / m_bpm));

		}
		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}
	}

}