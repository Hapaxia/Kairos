//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Absorel
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

#include "Absorel.hpp"

namespace kairos
{

Absorel::Absorel()
{
	absolute = 0;
	relative = 0.0;
}

Absorel::Absorel(int a, double r)
{
	absolute = a;
	relative = r;
}

Absorel Absorel::operator+(const Absorel& offset) const
{
	int resultAbsolute = static_cast<int>(std::floor(relative + offset.relative)) + absolute + offset.absolute;
	double resultRelative = (relative + offset.relative + absolute + offset.absolute) - resultAbsolute;
	return{ resultAbsolute, resultRelative };
}

Absorel Absorel::operator-(const Absorel& offset) const
{
	int resultAbsolute = static_cast<int>(std::floor((relative + absolute) - (offset.relative + offset.absolute)));
	double resultRelative = (relative + absolute) - (offset.relative + offset.absolute) - resultAbsolute;
	return{ resultAbsolute, resultRelative };
}

bool Absorel::operator<(const Absorel& position) const
{
	return (absolute + relative) < (position.absolute + position.relative);
}

bool Absorel::operator>(const Absorel& position) const
{
	return (absolute + relative) > (position.absolute + position.relative);
}

std::ostream& operator<<(std::ostream& out, const Absorel& position)
{
	out << position.absolute + position.relative;
	return out;
}

} // namespace Kairos
