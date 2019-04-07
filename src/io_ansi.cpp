/*
 *	ANSI codes for output (implementation)
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2019, IRIT UPS.
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

#include <elm/io/ansi.h>

namespace elm { namespace io {

/**
 * @class ANSIManager
 * This class is in charge of displaying ANSI code. Its main action is to disable
 * their display if the output stream does not support them.
 * @ingroup io
 */

/**
 */
void ANSIManager::print(io::Output& out, cstring text) {
	if(out.supportsANSI())
		out << text;
}


ANSICode
	PLAIN		("\x1B[0m"),	///< ANSI code for plain display
	BOLD		("\x1B[1m"),	///< ANSI code for bold text
	FAINT		("\x1B[2m"),	///< ANSI code for faint text
	ITALIC		("\x1B[3m"),	///< ANSI code for italic text
	UNDERLINE	("\x1B[4m"),	///< ANSI code for underlined text
	BLINK		("\x1B[5m"),	///< ANSI code for blink text
	RAPID_BLINK	("\x1B[6m"),	///< ANSI code for rapid blink text
	REVERSE		("\x1B[7m");	///< ANSI code for reverse mode text

ANSICode
	BLACK			("\x1B[30m"),	///< ANSI code for black text
	RED				("\x1B[31m"),	///< ANSI code for red text
	GREEN			("\x1B[32m"),	///< ANSI code for green text
	YELLOW			("\x1B[33m"),	///< ANSI code for yellow text
	BLUE			("\x1B[34m"),	///< ANSI code for blue text
	MAGENTA			("\x1B[35m"),	///< ANSI code for magenta text
	CYAN			("\x1B[36m"),	///< ANSI code for cyan text
	WHITE			("\x1B[37m"),	///< ANSI code for white text
	BRIGHT_BLACK	("\x1B[90m"),	///< ANSI code for bright black text
	BRIGHT_RED		("\x1B[91m"),	///< ANSI code for bright red text
	BRIGHT_GREEN	("\x1B[92m"),	///< ANSI code for bright green text
	BRIGHT_YELLOW	("\x1B[93m"),	///< ANSI code for bright yellow text
	BRIGHT_BLUE		("\x1B[94m"),	///< ANSI code for bright blue text
	BRIGHT_MAGENTA	("\x1B[95m"),	///< ANSI code for bright magenta text
	BRIGHT_CYAN		("\x1B[96m"),	///< ANSI code for bright cyan text
	BRIGHT_WHITE	("\x1B[97m");	///< ANSI code for bright white text

ANSICode
	BACK_BLACK			("\x1B[40m"),	///< ANSI code for black back
	BACK_RED			("\x1B[41m"),	///< ANSI code for red back
	BACK_GREEN			("\x1B[42m"),	///< ANSI code for green back
	BACK_YELLOW			("\x1B[43m"),	///< ANSI code for yellow back
	BACK_BLUE			("\x1B[44m"),	///< ANSI code for blue back
	BACK_MAGENTA		("\x1B[45m"),	///< ANSI code for magenta back
	BACK_CYAN			("\x1B[46m"),	///< ANSI code for cyan back
	BACK_WHITE			("\x1B[47m"),	///< ANSI code for white back
	BACK_BRIGHT_BLACK	("\x1B[100m"),	///< ANSI code for bright black back
	BACK_BRIGHT_RED		("\x1B[101m"),	///< ANSI code for bright red back
	BACK_BRIGHT_GREEN	("\x1B[102m"),	///< ANSI code for bright green back
	BACK_BRIGHT_YELLOW	("\x1B[103m"),	///< ANSI code for bright yellow back
	BACK_BRIGHT_BLUE	("\x1B[104m"),	///< ANSI code for bright blue back
	BACK_BRIGHT_MAGENTA	("\x1B[105m"),	///< ANSI code for bright magenta back
	BACK_BRIGHT_CYAN	("\x1B[106m"),	///< ANSI code for bright cyan back
	BACK_BRIGHT_WHITE	("\x1B[107m");	///< ANSI code for bright white back

} }	// elm::io
