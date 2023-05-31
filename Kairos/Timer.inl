//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Timer
//
// Copyright(c) 2014-2023 M.J.Silk
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

#ifndef KAIROS_TIMER_INL
#define KAIROS_TIMER_INL

#include "Timer.hpp"

namespace kairos
{

inline Timer::Timer()
	: m_isDone(true)
{
	m_stopwatch.stop();
}

inline void Timer::setTime(Duration& time)
{
	m_startTime = time;
	if (m_stopwatch.isPaused())
		reset();
	else
		restart();
}

// needs fixing
inline Duration Timer::getTime()
{
	if ((m_startTime - m_stopwatch.getTime()).nano < 0)
		stop();
	if (m_isDone)
		return m_stopwatch.getTime();
	else
		return m_startTime - m_stopwatch.getTime();
}

inline bool Timer::isDone() const
{
	return m_isDone;
}

inline bool Timer::isPaused() const
{
	return m_stopwatch.isPaused();
}

inline void Timer::start()
{
	if (getTime().nano > 0)
	{
		m_isDone = false;
		m_stopwatch.resume();
	}
}

inline void Timer::resume()
{
	start();
}

inline void Timer::pause()
{
	m_stopwatch.pause();
}

inline void Timer::stop()
{
	m_isDone = true;
	m_stopwatch.stop();
}

inline void Timer::finish()
{
	stop();
}

inline void Timer::reset()
{
	m_isDone = false;
	if (m_stopwatch.isPaused())
		m_stopwatch.stop();
	else
		m_stopwatch.restart();
}

inline void Timer::restart()
{
	m_isDone = false;
	m_stopwatch.restart();
}

} // namespace kairos
#endif // KAIROS_TIMER_INL
