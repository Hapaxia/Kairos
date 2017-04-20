//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Yalpes
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

#ifndef KAIROS_YALPES_HPP
#define KAIROS_YALPES_HPP

#include "Absorel.hpp"
#include "Duration.hpp"
#include "Stopwatch.hpp"
#include <vector>
#include <string>

namespace kairos
{

template <typename TData>
// Yalpes (playback event sequence) engine (v1.1.0)
class Yalpes
{
public:
	struct Event;
	class Track;

	std::vector<Track> tracks;

	Yalpes();
	void update();

	void moveEventsInQueueBeforeCurrentPositionToWaiting();
	void prepareEventQueue();

	void play();
	void stop();
	void pause();

	void seek(unsigned int positionAbsolute);
	void seek(unsigned int positionAbsolute, double positionRelative);
	void seek(const Absorel& position);
	void rewind();

	void setSpeed(double speed);
	void setSubsteps(unsigned int substeps);

	void automaticallyRemoveWaitingEventsOnNextUpdate();
	void doNotAutomaticallyRemoveWaitingEventsOnNextUpdate();

	bool isPlaying() const;
	Absorel getPosition() const;
	Duration getPlayTime() const;
	double getSpeed() const;
	unsigned int getSubsteps() const;
	std::string stringFromPosition(const Absorel& position) const;
	unsigned int getNumberOfTracks() const;
	unsigned int getNumberOfActiveTracks() const;

private:
	bool m_doAutomaticallyRemoveWaitingEventsOnNextUpdate{ true };
	bool m_isPlaying{ false };
	Stopwatch m_playbackClock;
	double m_speed{ 1.0 };
	unsigned int m_substeps{ 4u };
	Absorel m_currentPosition{ { 0, 0.0 } };
	Absorel m_playbackStartingPosition{ { 0, 0.0 } };
	unsigned int m_lengthInSteps{ 0u };

	void orderEvents(std::vector<Event>& events);
	std::string stringFromPositionWithSubsteps(const Absorel& position, unsigned int substeps) const;
	void resetEventsWaiting();
};

} // namespace kairos

#include "Yalpes.inl"

#endif // KAIROS_YALPES_HPP
