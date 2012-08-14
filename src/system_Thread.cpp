/*
 *	$Id$
 *	System class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2011, IRIT UPS.
 *
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <elm/assert.h>
#include <elm/sys/Thread.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

namespace elm { namespace sys {

/**
 * @class Runnable
 * A runnable must of the parent of any class representing a computation
 * performed in a thread.
 *
 * The user must overload the run() method in order to provided the computation
 * of the thread and may use the stop() method to stop the thread.
 *
 * Whatever, the end of run method stop also the thread.
 */


/**
 * @fn Runnable::run()
 * This method must be overloaded to provide the computation to the thread.
 */


/**
 * Cause the thread to stop immediatelly.
 */
void Runnable::stop(void) {
	thr->stop();
}


/**
 */
Thread::Thread(Runnable& runnable): _runnable(runnable) {

}


/**
 * PThread: implementation on Linux of threads
 */
class PThread: public Thread {
public:

	PThread(Runnable& runnable): Thread(runnable), running(false) { }

	// Thread overload
	virtual void start(void) throw(ThreadException) {
		int rc = pthread_create(&pt, NULL, PThread::run, this);
		if(rc < 0)
			throw ThreadException("no more thread available");
	}

	virtual void join(void) throw(ThreadException) {
		int rc = pthread_join(pt, NULL);
		if(rc < 0)
			throw ThreadException(strerror(errno));
	}

	virtual void kill(void) throw(ThreadException) {
		int rc = pthread_cancel(pt);
		if(rc < 0)
			throw ThreadException(strerror(errno));
	}

	virtual bool isRunning(void) {
		return running;
	}

protected:
	virtual void stop(void) {
		pthread_exit(NULL);
	}

private:
	pthread_t pt;
	bool running;

	static void cleanup(void *arg) {
		ASSERT(arg);
		PThread *thread = (PThread *)arg;
		thread->running = false;
	}

	static void *run(void *arg) {
		ASSERT(arg);
		PThread *thread = (PThread *)arg;
		pthread_cleanup_push(cleanup, thread);
		thread->running = true;
		thread->_runnable.run();
		pthread_cleanup_pop(1);
		return NULL;
	}

};


/**
 * Build a new thread for the given runnable.
 */
Thread *Thread::make(Runnable& runnable) {
	return new PThread(runnable);
}

//static Thread *current(void);

} }	// elm::sys
