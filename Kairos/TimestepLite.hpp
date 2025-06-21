//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Timestep Lite
//
// Copyright(c) 2015-2025 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

namespace kairos
{

class TimestepLite
{
public:
	TimestepLite();
	void addTimePassed(double timePassed);
	bool isStepProcessRequired();

	void setStep(double step);
	double getStep() const;
	double getOverall() const;

	void reset(); // resets both accumulator and overall to zero; does not affect the time step setting













private:
	double m_step;
	double m_accumulator;
	double m_overall;
};

inline TimestepLite::TimestepLite()
	: m_step{ 0.01 }
	, m_accumulator{ 0.0 }
	, m_overall{ 0.0 }
{
}

inline void TimestepLite::addTimePassed(const double timePassed)
{
	m_accumulator += timePassed;
}

inline bool TimestepLite::isStepProcessRequired()
{
	if (m_accumulator < m_step)
		return false;

	m_accumulator -= m_step;
	m_overall += m_step;
	return true;
}

inline void TimestepLite::setStep(const double step)
{
	constexpr double minStep{ 0.00001 };
	m_step = step < minStep ? 0.0 : step;
}

inline double TimestepLite::getStep() const
{
	return m_step;
}

inline double TimestepLite::getOverall() const
{
	return (m_overall > m_step) ? m_overall - m_step : 0.0;
}

inline void TimestepLite::reset()
{
	m_accumulator = 0.0;
	m_overall = 0.0;
}

} // namespace kairos
