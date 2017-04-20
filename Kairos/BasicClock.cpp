//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Basic Clock
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

#include "BasicClock.hpp"

#include <chrono>

namespace kairos
{

BasicClock::BasicClock()
	: m_secondsInOneMinute(60)
	, m_secondsInOneHour(3600)
	, m_secondsInOneDay(86400)
{
}

BasicClock::Time BasicClock::getCurrentTime() const
{
	return{ getCurrentHour(), getCurrentMinute(), getCurrentSecond() };
}

const unsigned int BasicClock::getCurrentHour() const
{
	return static_cast<unsigned int>(priv_getCurrentTimePointInSeconds() % m_secondsInOneDay / m_secondsInOneHour);
}

const unsigned int BasicClock::getCurrentMinute() const
{
	return static_cast<unsigned int>(priv_getCurrentTimePointInSeconds() % m_secondsInOneHour / m_secondsInOneMinute);
}

const unsigned int BasicClock::getCurrentSecond() const
{
	return static_cast<unsigned int>(priv_getCurrentTimePointInSeconds() % m_secondsInOneMinute);
}

const unsigned long long int BasicClock::priv_getCurrentTimePointInSeconds() const
{
	using std::chrono::system_clock;
	system_clock::time_point timePoint = system_clock::now();
	system_clock::duration duration = timePoint.time_since_epoch();
	return duration.count() * system_clock::period::num / system_clock::period::den;
}

} // namespace kairos
