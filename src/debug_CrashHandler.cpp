/*
 * $Id$
 * Copyright (c) 2007, IRIT - UPS
 *
 * CrashHandler class implementation
 */

#include <elm/debug/CrashHandler.h>
#include <elm/debug/GDBCrashHandler.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "../config.h"

namespace elm {

// handle SIGSEGV errors
static void handle_SIGSEGV(int sig, siginfo_t *info, void *context) {
	printf("FATAL: segmentation fault at %p.\n", info->si_addr);
	CrashHandler::crash();
}


// handle SIGILL errors
static void handle_SIGILL(int sig, siginfo_t *info, void *context) {
	printf("FATAL: illegal instruction at %p.\n", info->si_addr);
	CrashHandler::crash();
}


// handle SIGFPE errors
static void handle_SIGFPE(int sig, siginfo_t *info, void *context) {
	printf("FATAL: math float exception at %p.\n", info->si_addr);
	CrashHandler::crash();
}


/**
 * @class CrashHandler
 * This allows to provide customized handler for program crash. Currently,
 * there are only two: this default crash handler reverting to the program
 * abort and the @ref GDBCrashHandler.
 */


/**
 * Set the current crash handler.
 * @param handler	New crash handler.
 */
void CrashHandler::set(CrashHandler *handler) {
	if(current_handler)
		current_handler->cleanup();
	current_handler = handler;
	if(current_handler)
		current_handler->setup();
}


/**
 * @fn CrashHandler *CrashHandler::get(void);
 * Get the current crash handler.
 * @return	Current crash handler.
 */


/**
 * Initiate the crash of the program.
 * @warning no crash support is provided if the ELM_DEBUG environment variable
 * is set to "no".
 */
void CrashHandler::crash(void) {

	// Look for the ELM_DEBUG variable
	if(strcasecmp(getenv("ELM_DEBUG"), "no") == 0)
		abort();
	
	// Launch the crash handler
	current_handler->handle();
}


/**
 * Singleton of the default crash handler.
 */
CrashHandler CrashHandler::DEFAULT;


/**
 * @fn CrashHandler::CrashHandler(void);
 * Protected constructor to avoid multiple declaration.
 */


/**
 * This function is called when the handler is installed.
 */
void CrashHandler::setup(void) {
	struct sigaction sa;
	sa.sa_handler = 0;
	sa.sa_sigaction = handle_SIGSEGV;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_restorer = 0;
	sigaction(SIGSEGV, &sa, 0);
	sa.sa_sigaction = handle_SIGILL;
	sigaction(SIGILL, &sa, 0);
	sa.sa_sigaction = handle_SIGFPE;
	sigaction(SIGFPE, &sa, 0);
}


/**
 * This function is called when a crash need to be handled.
 */
void CrashHandler::handle(void) {
	abort();
}


/**
 * This function is called when the handler is removed.
 */
void CrashHandler::cleanup(void) {
	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sa.sa_sigaction = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_restorer = 0;
	sigaction(SIGSEGV, &sa, 0);
	sa.sa_handler = SIG_DFL;
	sigaction(SIGILL, &sa, 0);
	sa.sa_handler = SIG_DFL;
	sigaction(SIGFPE, &sa, 0);
}


/**
 * The current crash handler.
 */
CrashHandler *CrashHandler::current_handler = 0;


/* Initialize / finalize */
class CrashMonitor {
public:
	CrashMonitor(void) {
		CrashHandler::set(&CRASH_HANDLER);
	}
	inline ~CrashMonitor(void) {
		CrashHandler::set(0);
	}
};
static CrashMonitor _;

} // elm
