//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Fps Lite
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

#include "FpsLite.hpp"

namespace kairos
{

FpsLite::FpsLite()
	: m_framesPassed(0)
	, m_fps(0)
{
}

double FpsLite::getFps() const
{
	return m_fps;
}

void FpsLite::update()
{
	++m_framesPassed;
	if (clock.getTime().asSeconds() >= 1.0)
	{
		m_fps = m_framesPassed / clock.restart().asSeconds();
		m_framesPassed = 0;
	}
}

void FpsLite::reset()
{
	m_framesPassed = 0;
	clock.restart();
}

} // namespace kairos
