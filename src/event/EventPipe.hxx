/*
 * Copyright (C) 2003-2013 The Music Player Daemon Project
 * http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPD_EVENT_PIPE_HXX
#define MPD_EVENT_PIPE_HXX

#include "check.h"

#include <assert.h>

/**
 * A pipe that can be used to trigger an event to the read side.
 *
 * For optimization purposes, this class does not have a constructor
 * or a destructor.
 */
class EventPipe {
	int fds[2];

public:
#ifdef NDEBUG
	EventPipe() = default;
#else
	EventPipe():fds{-1, -1} {};
#endif

	EventPipe(const EventPipe &other) = delete;
	EventPipe &operator=(const EventPipe &other) = delete;

	bool Create();
	void Destroy();

	int Get() const {
		assert(fds[0] >= 0);
		assert(fds[1] >= 0);

		return fds[0];
	}

	/**
	 * Checks if Write() was called at least once since the last
	 * Read() call.
	 */
	bool Read();

	/**
	 * Wakes up the reader.  Multiple calls to this function will
	 * be combined to one wakeup.
	 */
	void Write();
};

#endif /* MAIN_NOTIFY_H */
