//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Absorel
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

// Signed number type represented using an 'abso'lute value (int) and a 'rel'ative value (double).
struct Absorel
{
	int absolute; // absolute position in "steps" from the start/origin (zero)
	double relative; // relative position in "steps" from absolute step (intended for use as alpha position/fraction part between steps)

	Absorel();
	Absorel(int a, double r);
	template <typename T>
	Absorel(const T& number); // create position from any number type
	template <typename Ta, typename Tr>
	Absorel(const Ta& a, const Tr& r); // create position from any absolute and relative pair. forcefully converts to int and double (using static_cast)

	template <typename T>
	Absorel operator+(const T& offset) const;
	Absorel operator+(const Absorel& offset) const;
	template <typename T>
	Absorel operator-(const T& offset) const;
	Absorel operator-(const Absorel& offset) const;
	template <typename T>
	Absorel operator*(const T& scale) const;
	template <typename T>
	Absorel operator/(const T& divisor) const;

	template <typename T>
	Absorel& operator+=(const T& offset);
	template <typename T>
	Absorel& operator-=(const T& offset);
	template <typename T>
	Absorel& operator*=(const T& scale);
	template <typename T>
	Absorel& operator/=(const T& divisor);

	bool operator<(const Absorel& position) const;
	bool operator>(const Absorel& position) const;
	friend std::ostream& operator<<(std::ostream& out, const Absorel& position);













private:
	template <typename T>
	Absorel priv_positionFromNumber(const T& n) const; // return position created from any number type
};

} // namespace kairos
#include <cmath>
namespace kairos
{

inline Absorel::Absorel()
	: absolute{ 0 }
	, relative{ 0.0 }
{
}

inline Absorel::Absorel(const int a, const double r)
	: absolute{ a }
	, relative{ r }
{
}

inline Absorel Absorel::operator+(const Absorel& offset) const
{
	const int resultAbsolute{ static_cast<int>(std::lround(std::floor(relative + offset.relative))) + absolute + offset.absolute };
	const double resultRelative{ (relative + offset.relative + absolute + offset.absolute) - resultAbsolute };
	return{ resultAbsolute, resultRelative };
}

inline Absorel Absorel::operator-(const Absorel& offset) const
{
	const int resultAbsolute{ static_cast<int>(std::lround(std::floor((relative + absolute) - (offset.relative + offset.absolute)))) };
	const double resultRelative{ (relative + absolute) - (offset.relative + offset.absolute) - resultAbsolute };
	return{ resultAbsolute, resultRelative };
}

inline bool Absorel::operator<(const Absorel& position) const
{
	return (absolute + relative) < (position.absolute + position.relative);
}

inline bool Absorel::operator>(const Absorel& position) const
{
	return (absolute + relative) > (position.absolute + position.relative);
}

inline std::ostream& operator<<(std::ostream& out, const Absorel& position)
{
	return (out << position.absolute + position.relative);
}

template <typename T>
inline Absorel::Absorel(const T& number)
{
	*this = priv_positionFromNumber(number);
}

template <typename Ta, typename Tr>
inline Absorel::Absorel(const Ta& a, const Tr& r)
{
	absolute = static_cast<int>(a);
	relative = static_cast<double>(r);
}

template <typename T>
inline Absorel Absorel::operator+(const T& offset) const
{
	const Absorel positionOffset{ offset };
	const int resultAbsolute{ static_cast<int>(std::floor(relative + positionOffset.relative)) + absolute + positionOffset.absolute };
	const double resultRelative{ (relative + positionOffset.relative + absolute + positionOffset.absolute) - resultAbsolute };
	return{ resultAbsolute, resultRelative };
}

template <typename T>
inline Absorel Absorel::operator-(const T& offset) const
{
	const Absorel positionOffset{ offset };
	const int resultAbsolute{ static_cast<int>(std::floor((relative + absolute) - (positionOffset.relative + positionOffset.absolute))) };
	const double resultRelative{ (relative + absolute) - (positionOffset.relative + positionOffset.absolute) - resultAbsolute };
	return{ resultAbsolute, resultRelative };
}

template <typename T>
inline Absorel Absorel::operator*(const T& scale) const
{
	return priv_positionFromNumber((relative + absolute) * scale);
}

template <typename T>
inline Absorel Absorel::operator/(const T& divisor) const
{
	return priv_positionFromNumber((relative + absolute) / divisor);
}

template <typename T>
inline Absorel& Absorel::operator+=(const T& offset)
{
	*this = *this + offset;
	return *this;
}

template <typename T>
inline Absorel& Absorel::operator-=(const T& offset)
{
	*this = *this - offset;
	return *this;
}

template <typename T>
inline Absorel& Absorel::operator*=(const T& scale)
{
	*this = *this * scale;
	return *this;
}

template <typename T>
inline Absorel& Absorel::operator/=(const T& divisor)
{
	*this = *this / divisor;
	return *this;
}

template <typename T>
inline Absorel Absorel::priv_positionFromNumber(const T& number) const
{
	const int resultAbsolute{ static_cast<int>(std::floor(static_cast<long double>(number))) };
	const double resultRelative{ static_cast<double>(static_cast<long double>(number) - resultAbsolute) };
	return{ resultAbsolute, resultRelative };
}

} // namespace kairos
