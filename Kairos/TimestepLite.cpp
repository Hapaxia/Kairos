//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Timestep Lite
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

#include "TimestepLite.hpp"

namespace kairos
{

TimestepLite::TimestepLite()
	: m_step(0.01)
	, m_accumulator(0.0)
	, m_overall(0.0)
{
}

void TimestepLite::update(double frameTime)
{
	m_accumulator += frameTime;
}

bool TimestepLite::isTimeToIntegrate()
{
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

void TimestepLite::setStep(double step)
{
	m_step = step;
	if (shouldBeZero(m_step))
		m_step = 0.0;
}

double TimestepLite::getStep() const
{
	return m_step;
}

double TimestepLite::getOverall() const
{
	return (m_overall > m_step) ? m_overall - m_step : 0.0;
}



// PRIVATE

bool TimestepLite::shouldBeZero(double a) const
{
	const double zeroEpsilon{ 0.00001 };
	return a < zeroEpsilon && a > -zeroEpsilon;
}

} // namespace kairos
