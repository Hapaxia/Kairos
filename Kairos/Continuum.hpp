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

#pragma once
#include "Stopwatch.hpp"

namespace kairos
{

class Continuum
{
public:
	Continuum();
	Duration reset();
	void go();
	void stop();
	void setSpeed(double speed);
	double getSpeed() const;
	void setTime(Duration time);
	Duration getTime() const;
	bool isStopped() const;
	double getSpeedDirectionMultiplier() const;













private:
	double m_speed;
	mutable Duration m_time;
	mutable Stopwatch m_stopwatch;

	void priv_update() const; // this not only updates m_time but also resets m_stopwatch to zero (does not affect its paused/running state)
};

inline Continuum::Continuum()
	: m_speed{ 1.0 }
	, m_time{}
	, m_stopwatch{}
{
}

inline Duration Continuum::reset()
{
	const Duration returnTime{ getTime() };
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
	priv_update();
	m_speed = speed;
}

inline double Continuum::getSpeed() const
{
	return m_speed;
}

inline void Continuum::setTime(const Duration time)
{
	priv_update();
	m_time = time;
}

inline Duration Continuum::getTime() const
{
	priv_update();
	return m_time;
}

inline bool Continuum::isStopped() const
{
	return m_stopwatch.isPaused();
}

inline double Continuum::getSpeedDirectionMultiplier() const
{
	return (m_speed > 0.0) ? 1.0 : (m_speed < 0.0) ? -1.0 : 0.0;
}

inline void Continuum::priv_update() const
{
	m_time += (m_stopwatch.isPaused() ? m_stopwatch.stop() : m_stopwatch.restart()) * m_speed;
}

} // namespace kairos
