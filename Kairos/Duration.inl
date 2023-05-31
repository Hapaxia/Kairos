//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Duration
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

#ifndef KAIROS_DURATION_INL
#define KAIROS_DURATION_INL

#include "Duration.hpp"

namespace kairos
{

inline Duration::Duration()
{
	zero();
}

inline Duration::Duration(long long int nanoseconds)
{
	nano = nanoseconds;
}

inline Duration::Duration(long int microseconds)
{
	nano = static_cast<long long int>(microseconds) * 1000;
}

inline Duration::Duration(int milliseconds)
{
	nano = static_cast<long long int>(milliseconds) * 1000000;
}

inline Duration::Duration(double seconds)
{
	nano = static_cast<long long int>(seconds * 1000000000.0);
}

inline Duration Duration::zero()
{
	Duration returnDuration{ *this };
	returnDuration.nano = nano;
	nano = 0;
	return returnDuration;
}

inline long long int Duration::asNanoseconds() const
{
	return nano;
}

inline long int Duration::asMicroseconds() const
{
	return static_cast<long int>(nano / 1000);
}

inline int Duration::asMilliseconds() const
{
	return static_cast<int>(nano / 1000000);
}

inline double Duration::asSeconds() const
{
	return static_cast<double>(nano) / 1000000000.0;
}

inline double Duration::asMinutes() const
{
	return asSeconds() / 60.0;
}

inline double Duration::asHours() const
{
	return asMinutes() / 24.0;
}



inline Duration& Duration::setFromHours(double hours)
{
	nano = static_cast<long long int>(hours * 3600000000000.0);
	return *this;
}

inline Duration& Duration::setFromMinutes(double minutes)
{
	nano = static_cast<long long int>(minutes * 60000000000.0);
	return *this;
}

inline Duration& Duration::setFromSeconds(double seconds)
{
	nano = static_cast<long long int>(seconds * 1000000000.0);
	return *this;
}

inline Duration& Duration::setFromMilliseconds(int milliseconds)
{
	nano = static_cast<long long int>(milliseconds) * 1000000;
	return *this;
}

inline Duration& Duration::setFromMicroseconds(long int microseconds)
{
	nano = static_cast<long long int>(microseconds) * 1000;
	return *this;
}

inline Duration& Duration::setFromNanoseconds(long long int nanoseconds)
{
	nano = nanoseconds;
	return *this;
}





inline Duration Duration::operator+(const Duration& offset) const
{
	Duration returnDuration{ *this };
	returnDuration.nano += offset.nano;
	return returnDuration;
}

inline Duration Duration::operator-(const Duration& offset) const
{
	Duration returnDuration{ *this };
	returnDuration.nano -= offset.nano;
	return returnDuration;
}

inline bool Duration::operator<(const Duration& rhs) const
{
	return nano < rhs.nano;
}

inline bool Duration::operator>(const Duration& rhs) const
{
	return nano > rhs.nano;
}

inline std::ostream& operator<<(std::ostream& out, const Duration& duration)
{
	double seconds = static_cast<double>(static_cast<long double>(duration.nano) / 1000000000);
	out << seconds << " seconds";
	return out;
}

} // namespace kairos
#endif // KAIROS_DURATION_INL
