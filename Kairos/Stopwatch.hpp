//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Stopwatch
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

// Pausable stopwatch

#pragma once
#include "Duration.hpp"
#include <chrono>

namespace kairos
{

class Stopwatch
{
public:
	Stopwatch();
	Duration getTime() const; // returns the current time
	Duration restart(); // resets time to zero and starts the timer
	Duration pause(); // stops timer
	Duration resume(); // starts timer
	Duration stop(); // stops timer and resets time to zero
	bool isPaused() const;













private:
	std::chrono::high_resolution_clock::time_point m_startTime;
	bool m_isPaused;
	Duration m_accumulatedDuration;
};

inline Stopwatch::Stopwatch()
	: m_startTime{ std::chrono::high_resolution_clock::now() }
	, m_isPaused{ false }
	, m_accumulatedDuration{}
{
}

inline Duration Stopwatch::getTime() const
{
	Duration elapsed{ m_accumulatedDuration };
	if (!m_isPaused)
		elapsed.nano += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_startTime).count();
	return elapsed;
}

inline Duration Stopwatch::restart()
{
	auto previousStartTime{ m_startTime };
	m_startTime = std::chrono::high_resolution_clock::now();

	Duration elapsed{ m_accumulatedDuration.zero() };
	if (!m_isPaused)
		elapsed.nano += std::chrono::duration_cast<std::chrono::nanoseconds>(m_startTime - previousStartTime).count();
	m_isPaused = false;
	return elapsed;
}

inline Duration Stopwatch::pause()
{
	m_accumulatedDuration = restart();
	m_isPaused = true;
	return m_accumulatedDuration;
}

inline Duration Stopwatch::resume()
{
	if (!m_isPaused)
		return getTime();
	m_accumulatedDuration = restart();
	m_isPaused = false;
	return m_accumulatedDuration;
}

inline Duration Stopwatch::stop()
{
	pause();
	return m_accumulatedDuration.zero();
}

inline bool Stopwatch::isPaused() const
{
	return m_isPaused;
}

} // namespace kairos
