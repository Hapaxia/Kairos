//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Duration
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

#pragma once
#include <ostream>

namespace kairos
{

// time duration
class Duration
{
public:
	long long int nano{ 0 };

	Duration();
	explicit Duration(long long int nanoseconds);
	explicit Duration(long int microseconds);
	explicit Duration(int milliseconds);
	Duration(double seconds);
	Duration zero();
	long long int asNanoseconds() const;
	long int asMicroseconds() const;
	int asMilliseconds() const;
	double asSeconds() const;
	double asMinutes() const;
	double asHours() const;

	Duration& setFromHours(double hours);
	Duration& setFromMinutes(double minutes);
	Duration& setFromSeconds(double seconds);
	Duration& setFromMilliseconds(int milliseconds);
	Duration& setFromMicroseconds(long int microseconds);
	Duration& setFromNanoseconds(long long int nanoseconds);

	Duration operator+(const Duration& offset) const;
	Duration operator-(const Duration& offset) const;
	template <typename T>
	Duration operator*(const T& scale) const;
	template <typename T>
	Duration operator/(const T& divisor) const;
	template <typename T>
	Duration& operator+=(const T& offset);
	template <typename T>
	Duration& operator-=(const T& offset);
	template <typename T>
	Duration& operator*=(const T& scale);
	template <typename T>
	Duration& operator/=(const T& divisor);
	bool operator<(const Duration& rhs) const;
	bool operator>(const Duration& rhs) const;
	bool operator<=(const Duration& rhs) const;
	bool operator>=(const Duration& rhs) const;
	friend std::ostream& operator<<(std::ostream& out, const Duration& duration);
};













inline Duration::Duration()
	: nano{ 0 }
{
}

inline Duration::Duration(const long long int nanoseconds)
{
	nano = nanoseconds;
}

inline Duration::Duration(const long int microseconds)
{
	nano = static_cast<long long int>(microseconds) * 1000;
}

inline Duration::Duration(const int milliseconds)
{
	nano = static_cast<long long int>(milliseconds) * 1000000;
}

inline Duration::Duration(const double seconds)
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



inline Duration& Duration::setFromHours(const double hours)
{
	nano = static_cast<long long int>(hours * 3600000000000.0);
	return *this;
}

inline Duration& Duration::setFromMinutes(const double minutes)
{
	nano = static_cast<long long int>(minutes * 60000000000.0);
	return *this;
}

inline Duration& Duration::setFromSeconds(const double seconds)
{
	nano = static_cast<long long int>(seconds * 1000000000.0);
	return *this;
}

inline Duration& Duration::setFromMilliseconds(const int milliseconds)
{
	nano = static_cast<long long int>(milliseconds) * 1000000;
	return *this;
}

inline Duration& Duration::setFromMicroseconds(const long int microseconds)
{
	nano = static_cast<long long int>(microseconds) * 1000;
	return *this;
}

inline Duration& Duration::setFromNanoseconds(const long long int nanoseconds)
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

inline bool Duration::operator<=(const Duration& rhs) const
{
	return nano <= rhs.nano;
}

inline bool Duration::operator>=(const Duration& rhs) const
{
	return nano >= rhs.nano;
}

inline std::ostream& operator<<(std::ostream& out, const Duration& duration)
{
	const double seconds{ static_cast<double>(static_cast<long double>(duration.nano) / 1000000000) };
	out << seconds << " seconds";
	return out;
}





template <typename T>
inline Duration Duration::operator*(const T& scale) const
{
	Duration returnDuration{ *this };
	returnDuration.nano = static_cast<long long int>(returnDuration.nano * scale);
	return returnDuration;
}

template <typename T>
inline Duration Duration::operator/(const T& divisor) const
{
	Duration returnDuration{ *this };
	returnDuration.nano = static_cast<long long int>(returnDuration.nano / divisor);
	return returnDuration;
}

template <typename T>
inline Duration& Duration::operator+=(const T& offset)
{
	*this = *this + offset;
	return *this;
}

template <typename T>
inline Duration& Duration::operator-=(const T& offset)
{
	*this = *this - offset;
	return *this;
}

template <typename T>
inline Duration& Duration::operator*=(const T& scale)
{
	*this = *this * scale;
	return *this;
}

template <typename T>
inline Duration& Duration::operator/=(const T& divisor)
{
	*this = *this / divisor;
	return *this;
}

} // namespace kairos
