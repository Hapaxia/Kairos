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

#ifndef KAIROS_FPSLITE_HPP
#define KAIROS_FPSLITE_HPP

#include "Stopwatch.hpp"

namespace kairos
{

class FpsLite
{
public:
	FpsLite();
	double getFps() const;
	void update(); // update should be called every frame
	void reset(); // restarts clock and resets number of frames passed to zero

private:
	Stopwatch clock;
	unsigned int m_framesPassed;
	double m_fps;
};

} // namespace kairos
#endif // KAIROS_FPSLITE_HPP
