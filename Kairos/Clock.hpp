//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Clock
//
// Copyright(c) 2025 M.J.Silk
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

// IMPORTANT NOTE: requires C++20

namespace kairos
{

class Clock
{
public:
	struct Time
	{
		unsigned int year{};
		unsigned int month{};
		unsigned int day{};
		unsigned int weekday{};
		unsigned int hour{};
		unsigned int minute{};
		unsigned int second{};
		unsigned int millisecond{};
	};

	Clock();

	void update();
	Time getTime() const;
	unsigned long int getTimeOfDaysInSeconds() const;
	unsigned long int getTimeOfDaysInMilliseconds() const;

	void setUseIsoEncoding(bool useIsoEncoding);
	bool getUseIsoEncoding() const;

	void setTimeZoneTzIdentifier(const std::string& tzIdentifier);
	std::string getTimeZoneTzIdentifier() const;
	std::string getActiveTimeZoneTzIdentifier() const;













private:
	bool m_useIsoEncoding;
	unsigned long int m_timeInMilliseconds;
	Time m_time;
	std::string m_timeZone_tzIdentifier;
	std::string m_activeTimeZone_tzIdentifier;

	void priv_update();
};

} // namespace kairos
#include <chrono>
namespace kairos
{

inline Clock::Clock()
	: m_useIsoEncoding{ true }
	, m_timeInMilliseconds{ 0u }
	, m_time{}
	, m_timeZone_tzIdentifier{ "" }
	, m_activeTimeZone_tzIdentifier{ "" }
{
}

inline void Clock::update()
{
	priv_update();
}

inline Clock::Time Clock::getTime() const
{
	return m_time;
}

inline unsigned long int Clock::getTimeOfDaysInSeconds() const
{
	return m_timeInMilliseconds / 1000u;
}

inline unsigned long int Clock::getTimeOfDaysInMilliseconds() const
{
	return m_timeInMilliseconds;
}

inline void Clock::setUseIsoEncoding(const bool useIsoEncoding)
{
	m_useIsoEncoding = useIsoEncoding;
}

inline bool Clock::getUseIsoEncoding() const
{
	return m_useIsoEncoding;
}

inline void Clock::setTimeZoneTzIdentifier(const std::string& tzIdentifier)
{
	m_timeZone_tzIdentifier = tzIdentifier;
}

inline std::string Clock::getTimeZoneTzIdentifier() const
{
	return m_timeZone_tzIdentifier;
}

inline std::string Clock::getActiveTimeZoneTzIdentifier() const
{
	return m_activeTimeZone_tzIdentifier;
}

inline void Clock::priv_update()
{
	bool isZoned{ false };
	const auto now{ std::chrono::system_clock::now() };
	std::chrono::system_clock::duration current{};
	std::chrono::local_time<std::chrono::system_clock::duration> local{};
	const std::chrono::time_zone* timeZone{};
	m_activeTimeZone_tzIdentifier = "";
	try
	{
		if (m_timeZone_tzIdentifier == "")
			timeZone = std::chrono::current_zone();
		else
		{
			try
			{
				timeZone = std::chrono::locate_zone(m_timeZone_tzIdentifier);
			}
			catch (...)
			{
				timeZone = std::chrono::current_zone();
			}
		}
		m_activeTimeZone_tzIdentifier = timeZone->name();
		const auto zt_local{ std::chrono::zoned_time{ timeZone, now } };
		local = zt_local.get_local_time();
		current = local.time_since_epoch();
		isZoned = true;
	}
	catch (...)
	{
		current = now.time_since_epoch();
	}

	constexpr unsigned long int m_secondsInOneMinute{ 60u };
	constexpr unsigned long int m_secondsInOneHour{ 3600u };
	constexpr unsigned long int m_secondsInOneDay{ 86400u };

	m_timeInMilliseconds = static_cast<unsigned long int>(std::chrono::duration_cast<std::chrono::milliseconds>(current).count() % (m_secondsInOneDay * 1000u));
	const auto timeInSeconds{ m_timeInMilliseconds / 1000u };
	m_time.hour = static_cast<unsigned int>(timeInSeconds / m_secondsInOneHour);
	m_time.minute = static_cast<unsigned int>(timeInSeconds % m_secondsInOneHour / m_secondsInOneMinute);
	m_time.second = static_cast<unsigned int>(timeInSeconds % m_secondsInOneMinute);
	m_time.millisecond = static_cast<unsigned int>(m_timeInMilliseconds % 1000u);

	std::chrono::year_month_day ymd{};
	if (isZoned)
		ymd = std::chrono::year_month_day{ std::chrono::floor<std::chrono::days>(local) };
	else
		ymd = std::chrono::year_month_day{ std::chrono::floor<std::chrono::days>(now) };

	m_time.year = static_cast<unsigned int>(static_cast<int>(ymd.year()));
	m_time.month = static_cast<unsigned int>(ymd.month());
	m_time.day = static_cast<unsigned int>(ymd.day());
	const auto weekday = std::chrono::weekday{ ymd };
	m_time.weekday = static_cast<unsigned int>(m_useIsoEncoding ? weekday.iso_encoding() : weekday.c_encoding());
}

} // namespace kairos
