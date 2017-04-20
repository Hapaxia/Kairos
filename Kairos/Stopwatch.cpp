//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Stopwatch
//
// Copyright(c) 2014-2017 M.J.Silk
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

#include "Stopwatch.hpp"

namespace kairos
{

using std::chrono::high_resolution_clock;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;

Stopwatch::Stopwatch()
	: m_startTime(high_resolution_clock::now())
	, m_isPaused(false)
{
}

Duration Stopwatch::getTime() const
{
	Duration elapsed{ m_accumulatedDuration };
	if (!m_isPaused)
		elapsed.nano += duration_cast<nanoseconds>(high_resolution_clock::now() - m_startTime).count();
	return elapsed;
}

Duration Stopwatch::restart()
{
	high_resolution_clock::time_point nowTime = high_resolution_clock::now();
	high_resolution_clock::time_point previousStartTime = m_startTime;
	m_startTime = nowTime;

	Duration elapsed{ m_accumulatedDuration.zero() };
	if (!m_isPaused)
		elapsed.nano += duration_cast<nanoseconds>(nowTime - previousStartTime).count();
	m_isPaused = false;
	return elapsed;
}

Duration Stopwatch::pause()
{
	m_accumulatedDuration = restart();
	m_isPaused = true;
	return m_accumulatedDuration;
}

Duration Stopwatch::resume()
{
	if (!m_isPaused)
		return getTime();
	m_accumulatedDuration = restart();
	m_isPaused = false;
	return m_accumulatedDuration;
}

Duration Stopwatch::stop()
{
	pause();
	return m_accumulatedDuration.zero();
}

bool Stopwatch::isPaused() const
{
	return m_isPaused;
}

} // namespace Kairos
