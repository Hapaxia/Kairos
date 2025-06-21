//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Timer
//
// Copyright(c) 2014-2025 M.J.Silk
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

// Pausable countdown timer

// "time" refers to amount of time remaining

#pragma once
#include "Duration.hpp"
#include "Stopwatch.hpp"

namespace kairos
{

class Timer
{
public:
	Timer();
	void setTime(const Duration& time); // sets a new start time which becomes the new current time
	Duration getTime(); // returns the current time. also acts as an "update"
	bool isDone() const; // returns true if timer has finished
	bool isPaused() const; // returns true if timer is currently paused (timer is also paused when it has finished)
	void start(); // begin counting down from current time
	void resume(); // alias of start()
	void pause(); // pauses counting down at current time
	void stop(); // finish counting down and reset time to zero
	void finish(); // alias of stop()
	void reset(); // sets the timer to the previously set (starting) time and stays paused if currently paused
	void restart(); // sets the timer to the previously set (starting) time and starts/resumes













private:
	bool m_isDone;
	Duration m_startTime;
	Stopwatch m_stopwatch;
};

inline Timer::Timer()
	: m_isDone{ true }
	, m_startTime{}
	, m_stopwatch{}
{
	m_stopwatch.stop();
}

inline void Timer::setTime(const Duration& time)
{
	m_startTime = time;
	if (m_stopwatch.isPaused())
		reset();
	else
		restart();
}

inline Duration Timer::getTime()
{
	const Duration currentTime{ m_startTime - m_stopwatch.getTime() };
	if (currentTime.nano <= 0)
		stop();
	if (m_isDone)
		return {};
	else
		return currentTime;
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

} // namespace Kairos
