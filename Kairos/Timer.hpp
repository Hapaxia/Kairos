//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Timer
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

// WARNING: C++11 or later required (uses <chrono>)

// Pausable countdown timer

// "time" refers to time remaining

#ifndef KAIROS_TIMER_HPP
#define KAIROS_TIMER_HPP

#include "Duration.hpp"
#include "Stopwatch.hpp"

namespace kairos
{

class Timer
{
public:
	Timer();
	void setTime(Duration& time); // sets a new start time which becomes the new current time
	Duration getTime(); // returns the current time. also acts as an "update"
	bool isDone() const; // returns true if timer has finished
	bool isPaused() const; // returns true if timer has finished
	void start(); // begin counting down
	void resume(); // alias of start()
	void pause(); // stop counting down at current time
	void stop(); // finish counting down and reset time to zero
	void finish(); // alias of stop()
	void reset(); // sets the timer to the previously set (starting) time and pauses
	void restart(); // reset(), resume()

private:
	Stopwatch m_stopwatch;
	Duration m_startTime;
	bool m_isDone;
};

} // namespace Kairos
#endif // KAIROS_TIMER_HPP
