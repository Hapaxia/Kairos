//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Timestep
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

#ifndef KAIROS_TIMESTEP_HPP
#define KAIROS_TIMESTEP_HPP

#include "Continuum.hpp"

namespace kairos
{

class Timestep
{
public:
	Timestep();
	void setStep(double step);
	double getStep() const;
	float getStepAsFloat() const;
	void resetTime();
	bool isUpdateRequired();
	double getInterpolationAlpha() const;
	float getInterpolationAlphaAsFloat() const;
	void addFrame();
	double getOverall() const; // amount of time processed (whole steps only)
	float getOverallAsFloat() const;
	double getTime() const; // amount of time accumulated
	float getTimeAsFloat() const;
	void setMaxAccumulation(double maxAccumulation);
	void setTimeSpeed(double timeSpeed);
	double getTimeSpeed() const;
	void pause();
	void unpause();
	bool isPaused() const;

private:
	Continuum m_continuum;
	double m_step;
	double m_accumulator;
	double m_overall;
	double m_maxAccumulation;
	double m_timeSpeed;

	bool shouldBeZero(double a) const;
};

} // namespace kairos
#endif // KAIROS_TIMESTEP_HPP
