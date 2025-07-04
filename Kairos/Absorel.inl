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

#ifndef KAIROS_ABSOREL_INL
#define KAIROS_ABSOREL_INL

#include "Absorel.hpp"

#include <cmath>

namespace kairos
{

inline Absorel::Absorel()
{
	absolute = 0;
	relative = 0.0;
}

inline Absorel::Absorel(int a, double r)
{
	absolute = a;
	relative = r;
}

inline Absorel Absorel::operator+(const Absorel& offset) const
{
	int resultAbsolute = static_cast<int>(std::floor(relative + offset.relative)) + absolute + offset.absolute;
	double resultRelative = (relative + offset.relative + absolute + offset.absolute) - resultAbsolute;
	return{ resultAbsolute, resultRelative };
}

inline Absorel Absorel::operator-(const Absorel& offset) const
{
	int resultAbsolute = static_cast<int>(std::floor((relative + absolute) - (offset.relative + offset.absolute)));
	double resultRelative = (relative + absolute) - (offset.relative + offset.absolute) - resultAbsolute;
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
	out << position.absolute + position.relative;
	return out;
}

template <typename T>
inline Absorel::Absorel(const T& number)
{
	*this = positionFromNumber(number);
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
	Absorel positionOffset{ offset };
	int resultAbsolute = static_cast<int>(std::floor(relative + positionOffset.relative)) + absolute + positionOffset.absolute;
	double resultRelative = (relative + positionOffset.relative + absolute + positionOffset.absolute) - resultAbsolute;
	return{ resultAbsolute, resultRelative };
}

template <typename T>
inline Absorel Absorel::operator-(const T& offset) const
{
	Absorel positionOffset{ offset };
	int resultAbsolute = static_cast<int>(std::floor((relative + absolute) - (positionOffset.relative + positionOffset.absolute)));
	double resultRelative = (relative + absolute) - (positionOffset.relative + positionOffset.absolute) - resultAbsolute;
	return{ resultAbsolute, resultRelative };
}

template <typename T>
inline Absorel Absorel::operator*(const T& scale) const
{
	return positionFromNumber((relative + absolute) * scale);
}

template <typename T>
inline Absorel Absorel::operator/(const T& divisor) const
{
	return positionFromNumber((relative + absolute) / divisor);
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
inline Absorel Absorel::positionFromNumber(const T& number) const
{
	int resultAbsolute = static_cast<int>(std::floor(static_cast<long double>(number)));
	double resultRelative = static_cast<double>(static_cast<long double>(number)-resultAbsolute);
	return{ resultAbsolute, resultRelative };
}

} // namespace kairos
#endif // KAIROS_ABSOREL_INL
