//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Basic Clock
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
#include <chrono>

namespace kairos
{

class BasicClock
{
public:
	struct Time
	{
		unsigned int hour{};
		unsigned int minute{};
		unsigned int second{};
	};

	BasicClock()							: m_secondsInOneMinute{ 60u }, m_secondsInOneHour{ 3600u }, m_secondsInOneDay{ 86400u } {}
	Time getCurrentTime() const				{ return{ getCurrentHour(), getCurrentMinute(), getCurrentSecond() }; }
	unsigned int getCurrentHour() const		{ return static_cast<unsigned int>(priv_getCurrentTimePointInSeconds() % m_secondsInOneDay / m_secondsInOneHour); }
	unsigned int getCurrentMinute() const	{ return static_cast<unsigned int>(priv_getCurrentTimePointInSeconds() % m_secondsInOneHour / m_secondsInOneMinute); }
	unsigned int getCurrentSecond() const	{ return static_cast<unsigned int>(priv_getCurrentTimePointInSeconds() % m_secondsInOneMinute); }







private:
	const unsigned long int m_secondsInOneMinute;
	const unsigned long int m_secondsInOneHour;
	const unsigned long int m_secondsInOneDay;

	unsigned long long int priv_getCurrentTimePointInSeconds() const
	{ return std::chrono::system_clock::now().time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den; }
};

} // namespace kairos
