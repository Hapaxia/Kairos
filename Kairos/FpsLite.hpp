//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Fps Lite
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

class FpsLite
{
public:
	FpsLite()								:m_framesPassed{ 0u }, m_fps{ 0.0 }, m_updateDelay{ 1.0 }, m_clock{} {}
	void addFrame();						// addFrame should be called every frame
	double getFps() const					{ return m_fps; }
	void setUpdateDelay(double updateDelay)	{ m_updateDelay = updateDelay; }
	void reset()							{ m_framesPassed = 0u; m_clock.restart(); }; // restarts clock and resets number of frames passed to zero

private:
	std::size_t m_framesPassed;
	double m_fps;
	double m_updateDelay;
	Stopwatch m_clock;
};

inline void FpsLite::addFrame()
{
	++m_framesPassed;
	if (m_clock.getTime().asSeconds() >= m_updateDelay)
	{
		m_fps = static_cast<double>(m_framesPassed) / m_clock.restart().asSeconds();
		m_framesPassed = 0u;
	}
}

} // namespace kairos
