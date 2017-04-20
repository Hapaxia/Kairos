//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Timestep
//
// Copyright(c) 2015-2017 M.J.Silk
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

#include "Timestep.hpp"

namespace kairos
{

Timestep::Timestep()
	: m_step(0.01)
	, m_accumulator(0.0)
	, m_overall(0.0)
	, m_maxAccumulation(0.1)
	, m_timeSpeed(1.0)
{
}

void Timestep::setStep(double step)
{
	m_step = step;
	if (shouldBeZero(m_step))
		m_step = 0.0;
	setMaxAccumulation(m_maxAccumulation);
}

double Timestep::getStep() const
{
	return m_step;
}

float Timestep::getStepAsFloat() const
{
	return static_cast<float>(getStep());
}

void Timestep::resetTime()
{
	m_continuum.reset();
	m_overall = 0.0;
}

bool Timestep::isUpdateRequired()
{
	if (m_accumulator > m_maxAccumulation)
		m_accumulator = m_maxAccumulation;
	if ((m_step > 0.0) && (m_accumulator >= m_step))
	{
		m_accumulator -= m_step;
		m_overall += m_step;
		return true;
	}
	else if ((m_step < 0.0) && (m_accumulator <= m_step))
	{
		m_accumulator -= m_step;
		m_overall += m_step;
		return true;
	}
	else
		return false;
}

double Timestep::getInterpolationAlpha() const
{
	return m_accumulator < m_step ? m_accumulator / m_step : 1.0;
}

float Timestep::getInterpolationAlphaAsFloat() const
{
	return static_cast<float>(getInterpolationAlpha());
}

void Timestep::addFrame()
{
	double frameTime{ m_continuum.reset().asSeconds() };
	m_continuum.setSpeed(m_timeSpeed);
	m_accumulator += frameTime;
}

double Timestep::getOverall() const
{
	return (m_overall > m_step) ? m_overall - m_step : 0.0;
}

float Timestep::getOverallAsFloat() const
{
	return static_cast<float>(getOverall());
}

double Timestep::getTime() const
{
	return getOverall() + getInterpolationAlpha() * getStep();
}

float Timestep::getTimeAsFloat() const
{
	return static_cast<float>(getTime());
}
void Timestep::setMaxAccumulation(double maxAccumulation)
{
	m_maxAccumulation = maxAccumulation < m_step ? m_step : maxAccumulation;
}

void Timestep::setTimeSpeed(double timeSpeed)
{
	m_timeSpeed = timeSpeed;
	m_continuum.setSpeed(m_timeSpeed);
}

double Timestep::getTimeSpeed() const
{
	return m_timeSpeed;
}

void Timestep::pause()
{
	m_continuum.stop();
}

void Timestep::unpause()
{
	m_continuum.go();
}

bool Timestep::isPaused() const
{
	return m_continuum.isStopped();
}



// PRIVATE

bool Timestep::shouldBeZero(double a) const
{
	const double zeroEpsilon{ 0.00001 };
	return a < zeroEpsilon && a > -zeroEpsilon;
}

} // namespace kairos
