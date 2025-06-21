//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Timestep
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
#include "Continuum.hpp"

namespace kairos
{

class Timestep
{
public:
	Timestep();
	void setStep(double step); // must be positive (or zero)
	double getStep() const;
	float getStepAsFloat() const;
	void resetTime();
	bool isUpdateRequired();
	double getInterpolationAlpha() const;
	float getInterpolationAlphaAsFloat() const;
	void addFrame();
	double getOverall() const; // amount of time processed - whole steps only - in either time direction
	float getOverallAsFloat() const;
	double getTime() const; // current time; this can move positively or negatively and depends on time speed
	float getTimeAsFloat() const;
	void setMaxAccumulation(double maxAccumulation);
	void setTimeSpeed(double timeSpeed);
	double getTimeSpeed() const;
	void pause();
	void unpause();
	bool isPaused() const;
	int getTimeDirection() const;













private:
	const double m_zeroEpsilon;
	const double m_minStep;
	double m_step;
	double m_accumulator;
	double m_overall;
	double m_maxAccumulation;
	double m_timeSpeed;
	double m_time;
	Continuum m_continuum;
};

} // namespace kairos
#include <cmath>
namespace kairos
{

inline Timestep::Timestep()
	: m_zeroEpsilon{ 0.00001 }
	, m_minStep{ 0.00001 }
	, m_step{ 0.01 }
	, m_accumulator{ 0.0 }
	, m_overall{ 0.0 }
	, m_maxAccumulation{ 0.1 }
	, m_timeSpeed{ 1.0 }
	, m_time{ 0.0 }
	, m_continuum{}
{
}

inline void Timestep::setStep(const double step)
{
	m_step = step < m_minStep ? 0.0 : step;
	setMaxAccumulation(m_maxAccumulation);
}

inline double Timestep::getStep() const
{
	return m_step;
}

inline float Timestep::getStepAsFloat() const
{
	return static_cast<float>(getStep());
}

inline void Timestep::resetTime()
{
	m_continuum.reset();
	m_overall = 0.0;
	m_time = 0.0;
}

inline bool Timestep::isUpdateRequired()
{
	if (m_accumulator > m_maxAccumulation)
		m_accumulator = m_maxAccumulation;
	if ((m_step > 0.0) && (m_accumulator >= m_step))
	{
		m_accumulator -= m_step;
		m_overall += m_step;
		m_time += m_step * m_continuum.getSpeedDirectionMultiplier();
		return true;
	}
	return false;
}

inline double Timestep::getInterpolationAlpha() const
{
	if (m_step < m_minStep)
		return 0.0;
	return (m_accumulator < m_step) ? (m_accumulator / m_step) : 1.0;
}

inline float Timestep::getInterpolationAlphaAsFloat() const
{
	return static_cast<float>(getInterpolationAlpha());
}

inline void Timestep::addFrame()
{
	const double frameTime{ m_continuum.reset().asSeconds() };
	m_continuum.setSpeed(m_timeSpeed);
	m_accumulator += std::abs(frameTime);
}

inline double Timestep::getOverall() const
{
	return (m_overall > m_step) ? m_overall - m_step : 0.0;
}

inline float Timestep::getOverallAsFloat() const
{
	return static_cast<float>(getOverall());
}

inline double Timestep::getTime() const
{
	return m_time + (getInterpolationAlpha() * getStep() * m_continuum.getSpeedDirectionMultiplier());
}

inline float Timestep::getTimeAsFloat() const
{
	return static_cast<float>(getTime());
}
inline void Timestep::setMaxAccumulation(const double maxAccumulation)
{
	m_maxAccumulation = maxAccumulation < m_step ? m_step : maxAccumulation;
}

inline void Timestep::setTimeSpeed(const double timeSpeed)
{
	m_timeSpeed = (std::abs(timeSpeed) < m_zeroEpsilon) ? 0.0 : timeSpeed;
	m_continuum.setSpeed(m_timeSpeed);
}

inline double Timestep::getTimeSpeed() const
{
	return m_timeSpeed;
}

inline void Timestep::pause()
{
	m_continuum.stop();
}

inline void Timestep::unpause()
{
	m_continuum.go();
}

inline bool Timestep::isPaused() const
{
	return m_continuum.isStopped();
}

inline int Timestep::getTimeDirection() const
{
	return (m_timeSpeed < 0.0) ? -1 : (m_timeSpeed > 0.0) ? 1 : 0;
}

} // namespace kairos
