//////////////////////////////////////////////////////////////////////////////
//
// Kairos
// --
//
// Yalpes
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
#include "Absorel.hpp"
#include "Duration.hpp"
#include "Stopwatch.hpp"
#include <vector>
#include <string>

namespace kairos
{

template <typename TData = int>
// Yalpes (playback event sequence) engine (v1.2.0)
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
	void setSubsteps(std::size_t substeps);

	void setAutomaticallyRemoveWaitingEventsOnNextUpdate(bool automaticallyRemoveWaitingEventsOnNextUpdate);

	bool isPlaying() const;
	Absorel getPosition() const;
	Duration getPlayTime() const;
	double getSpeed() const;
	std::size_t getSubsteps() const;
	std::string stringFromPosition(const Absorel& position) const;
	std::size_t getNumberOfTracks() const;
	std::size_t getNumberOfActiveTracks() const;













private:
	bool m_doAutomaticallyRemoveWaitingEventsOnNextUpdate;
	bool m_isPlaying;
	double m_speed;
	std::size_t m_substeps;
	Absorel m_currentPosition;
	Absorel m_playbackStartingPosition;
	std::size_t m_lengthInSteps;
	Stopwatch m_playbackClock;

	void priv_resetEventsWaiting();
};

} // namespace kairos
#include <algorithm> // for std::sort
#include <cmath>
namespace kairos
{

/*******************
*                  *
*  YALPES STRUCTS  *
*                  *
*******************/

template <typename TData>
// An event stores 1 int, 1 double, 1 std::size_t, and 1 of the passed-in datatype (TData)
struct Yalpes<TData>::Event
{
	Absorel position{ 0, 0.0 };
	std::size_t type{ 0u };
	TData data{};

	bool operator<(const Event& e) const; // allows sorting of the events (sorts using position)
	bool operator>(const Event& e) const;
};

template <typename TData>
// Individual track of events that run in parallel with the other tracks
class Yalpes<TData>::Track
{
public:
	std::vector<Event> events;
	std::vector<Event> eventQueue;
	std::vector<Event> eventsWaiting;

	Track();
	void setIsActive(bool isActive);
	bool getIsActive() const;

private:
	bool m_isActive;
};


































/***********************************
*                                  *
*  YALPES TEMPLATE IMPLEMENTATION  *
*                                  *
***********************************/

template <typename TData>
inline Yalpes<TData>::Yalpes()
	: tracks(1u)
	, m_doAutomaticallyRemoveWaitingEventsOnNextUpdate{ true }
	, m_isPlaying{ false }
	, m_speed{ 1.0 }
	, m_substeps{ 4u }
	, m_currentPosition{ 0, 0.0 }
	, m_playbackStartingPosition{ 0, 0.0 }
	, m_lengthInSteps{ 0u }
	, m_playbackClock{}
{
}

template <typename TData>
inline void Yalpes<TData>::update()
{
	if (m_isPlaying)
	{
		if (m_currentPosition > Absorel{ m_lengthInSteps })
		{
			pause();
			rewind();
		}
		else
		{
			const double currentPlayClock = getPlayTime().asSeconds();
			m_currentPosition = m_playbackStartingPosition + Absorel{ currentPlayClock * m_speed };
			if (m_doAutomaticallyRemoveWaitingEventsOnNextUpdate)
				priv_resetEventsWaiting();
			moveEventsInQueueBeforeCurrentPositionToWaiting();
		}
	}
}

template <typename TData>
inline void Yalpes<TData>::moveEventsInQueueBeforeCurrentPositionToWaiting()
{
	for (auto& track : tracks)
	{
		std::size_t numberOfEventsToRemove{ 0u };

		// copy to events waiting
		for (auto& e : track.eventQueue)
		{
			if (e.position < m_currentPosition)
			{
				track.eventsWaiting.push_back(e);
				++numberOfEventsToRemove;
			}
		}

		// remove from events queue
		if (numberOfEventsToRemove > 0u)
			track.eventQueue.erase(track.eventQueue.begin(), track.eventQueue.begin() + numberOfEventsToRemove);
	}
}

template <typename TData>
inline void Yalpes<TData>::prepareEventQueue()
{
	unsigned int latestStep{ 0u };
	priv_resetEventsWaiting();
	for (auto& track : tracks)
	{
		track.eventQueue.clear();
		for (auto& e : track.events)
		{
			track.eventQueue.push_back(e);
			if (latestStep < (e.position.absolute + e.position.relative))
				latestStep = static_cast<unsigned int>(std::lround(std::ceil(e.position.absolute + e.position.relative)));
		}
		std::sort(track.eventQueue.begin(), track.eventQueue.end());
	}
	moveEventsInQueueBeforeCurrentPositionToWaiting();
	priv_resetEventsWaiting();
	m_lengthInSteps = latestStep;
}

template <typename TData>
inline void Yalpes<TData>::play()
{
	m_playbackStartingPosition = m_currentPosition;
	prepareEventQueue();
	m_isPlaying = true;
	m_playbackClock.restart();
}

template <typename TData>
inline void Yalpes<TData>::stop()
{
	pause();
	rewind();
}

template <typename TData>
inline void Yalpes<TData>::pause()
{
	moveEventsInQueueBeforeCurrentPositionToWaiting();
	priv_resetEventsWaiting();
	m_isPlaying = false;
}

template <typename TData>
inline void Yalpes<TData>::seek(const unsigned int positionAbsolute)
{
	seek(positionAbsolute, 0.0);
}

template <typename TData>
inline void Yalpes<TData>::seek(const Absorel& position)
{
	seek(static_cast<unsigned int>(position.absolute), position.relative);
}

template <typename TData>
inline void Yalpes<TData>::seek(unsigned int positionAbsolute, double positionRelative)
{
	constexpr unsigned int minStep{ 0u };
	if ((positionAbsolute < minStep) || (positionRelative + positionAbsolute < minStep))
	{
		positionAbsolute = minStep;
		positionRelative = 0.0;
	}
	m_currentPosition = { static_cast<int>(positionAbsolute), positionRelative };
	m_playbackStartingPosition = m_currentPosition;
	pause();
}

template <typename TData>
inline void Yalpes<TData>::rewind()
{
	seek(0u);
}

template <typename TData>
inline bool Yalpes<TData>::isPlaying() const
{
	return m_isPlaying;
}

template <typename TData>
inline Absorel Yalpes<TData>::getPosition() const
{
	return m_currentPosition;
}

template <typename TData>
inline Duration Yalpes<TData>::getPlayTime() const
{
	return m_playbackClock.getTime();
}

template <typename TData>
inline double Yalpes<TData>::getSpeed() const
{
	return m_speed;
}

template <typename TData>
inline std::size_t Yalpes<TData>::getSubsteps() const
{
	return m_substeps;
}

template <typename TData>
inline std::size_t Yalpes<TData>::getNumberOfTracks() const
{
	return tracks.size();
}

template <typename TData>
inline std::size_t Yalpes<TData>::getNumberOfActiveTracks() const
{
	std::size_t total{ 0u };
	for (auto& track : tracks)
	{
		if (track.getIsActive())
			++total;
	}
	return total;
}


template <typename TData>
inline void Yalpes<TData>::setSpeed(const double speed)
{
	constexpr double minSpeed{ 1.0 };
	constexpr double maxSpeed{ 1000.0 };
	if ((speed >= minSpeed) && (speed <= maxSpeed))
		m_speed = speed;
}

template <typename TData>
inline void Yalpes<TData>::setSubsteps(const std::size_t substeps)
{
	m_substeps = substeps;
}

template<typename TData>
inline void Yalpes<TData>::setAutomaticallyRemoveWaitingEventsOnNextUpdate(const bool automaticallyRemoveWaitingEventsOnNextUpdate)
{
	m_doAutomaticallyRemoveWaitingEventsOnNextUpdate = automaticallyRemoveWaitingEventsOnNextUpdate;
}

template <typename TData>
inline std::string Yalpes<TData>::stringFromPosition(const Absorel& position) const
{
	return std::to_string(position.absolute) + ":" + std::to_string(static_cast<int>(std::floor(position.relative * m_substeps)));
}

// PRIVATE

template <typename TData>
inline void Yalpes<TData>::priv_resetEventsWaiting()
{
	for (auto& track : tracks)
		track.eventsWaiting.clear();
}

























/*****************************************
*                                        *
*  YALPES TRACK TEMPLATE IMPLEMENTATION  *
*                                        *
*****************************************/

template <typename TData>
inline Yalpes<TData>::Track::Track()
	: m_isActive{ true }
{
}

template <typename TData>
inline void Yalpes<TData>::Track::setIsActive(const bool isActive)
{
	m_isActive = isActive;
	if (!m_isActive)
	{
		eventQueue.clear();
		eventsWaiting.clear();
	}
}

template <typename TData>
inline bool Yalpes<TData>::Track::getIsActive() const
{
	return m_isActive;
}























/*****************************************
*                                        *
*  YALPES EVENT TEMPLATE IMPLEMENTATION  *
*                                        *
*****************************************/

template <typename TData>
inline bool Yalpes<TData>::Event::operator<(const Event& e) const
{
	return (position.absolute + position.relative) < (e.position.absolute + e.position.relative);
}

template <typename TData>
inline bool Yalpes<TData>::Event::operator>(const Event& e) const
{
	return (position.absolute + position.relative) > (e.position.absolute + e.position.relative);
}

} // namespace kairos
