/*
 * $Id$
 * Copyright (c) 2007, IRIT - UPS
 *
 * CrashHandler class interface
 */
#ifndef ELM_DEBUG_CRASH_HANDLER_H
#define ELM_DEBUG_CRASH_HANDLER_H

namespace elm {
	
// CrashHandler class
class CrashHandler {
public:
	static void set(CrashHandler *handler);
	static inline CrashHandler *get(void) { return current_handler; }
	static void crash(void);
	static CrashHandler DEFAULT;

	virtual void setup(void);
	virtual void handle(void);
	virtual void cleanup(void);

protected:
	inline CrashHandler(void) { }
	virtual ~CrashHandler(void) { }

private:
	static CrashHandler *current_handler; 
};

// NoCrashHandler class
class NoCrashHandler: public CrashHandler {
public:
	virtual void setup(void) { }
	virtual void handle(void) { }
	virtual void cleanup(void) { }
};

} // elm

#endif // ELM_DEBUG_CRASH_HANDLER_H
