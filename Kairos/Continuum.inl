//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Continuum
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

#ifndef KAIROS_CONTINUUM_INL
#define KAIROS_CONTINUUM_INL

#include "Continuum.hpp"

namespace kairos
{

inline Continuum::Continuum()
	: m_stopwatch()
	, m_time()
	, m_speed(1.0)
{
}

inline Duration Continuum::reset()
{
	Duration returnTime{ getTime() };
	m_stopwatch.restart();
	m_time.zero();
	m_speed = 1.0;
	return returnTime;
}

inline void Continuum::go()
{
	m_stopwatch.resume();
}

inline void Continuum::stop()
{
	m_stopwatch.pause();
}

inline void Continuum::setSpeed(const double speed)
{
	updateTime();
	m_speed = speed;
}

inline double Continuum::getSpeed() const
{
	return m_speed;
}

inline void Continuum::setTime(Duration time)
{
	updateTime();
	m_time = time;
}

inline Duration Continuum::getTime() const
{
	updateTime();
	return m_time;
}

inline bool Continuum::isStopped() const
{
	return m_stopwatch.isPaused();
}



// PRIVATE

inline void Continuum::updateTime() const
{
	const bool isStopped{ m_stopwatch.isPaused() };
	m_time += m_stopwatch.restart() * m_speed;
	if (isStopped)
		m_stopwatch.stop();
}

} // namespace kairos
#endif // KAIROS_CONTINUUM_INL
