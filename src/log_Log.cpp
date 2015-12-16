/*
 *	elm::log::Debug class implementation
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
#include <elm/log/Log.h>

/** @defgroup log Logging and pretty-printing
 *  Module for parametrized pretty-printing logs on the console, with colors, automatically prefixed by source path and such.
 */

namespace elm { namespace color {
/**
 * @class Color
 * @ingroup log
 * @brief Define ANSI colors (including foreground, background, bold and underline) for global use in std C/elm strings/outstreams, using implicit type conversions.
 */
}}

namespace elm { namespace log {
/**
 * @class Debug
 * @ingroup log
 * @brief Provide necessary static methods for the use of ELM_DBG* macros.
 */


/**
 * @ingroup log
 * @var int flags;
 * @brief Flags to set for the debugging macros.
 * * DEBUG: Enable debugging\n
 * * SOURCE_INFO: Display the source path (with line numbers)\n
 * * NUMBERING: Number the log lines\n
 * * COLOR/COLORS: Use colors
 */
int flags = DEBUG |	COLOR | SOURCE_INFO | NUMBERING; // default to enabled debugging with colors, prefixed by source path and log line numbers

/**
 * @ingroup log
 * @var int verbose_level;
 * @brief Verbose bit mask.
 * ELM_DBGV will only be enabled if the provided parameter level & verbose_level is non-null  
 */
int verbose_level = 0xffff; // default to activate everything 

/**
 * @ingroup log
 * @var int srcpath_length;
 * @brief Numeric value that defines the constant length of the source path in the prefix.
 * @warning: must be > 3
 */
int srcpath_length = 20; // default to 20 characters

/**
 * @ingroup log
 * @var elm::color::Color prefix_color;
 * @brief Color used for printing the prefix message.
 * The default value is elm::color::Yel
 */
elm::color::Color prefix_color = elm::color::Yel;

/**
 * @ingroup log
 * @def ELM_DBG(str);
 * @param str the string to print
 * @brief Format and output the string str on the log, depending on the global parameters set in flags and srcpath_length.\n
 * If ELM_NO_DBG is not defined, the alias DBG is available.
 */

/**
 * @ingroup log
 * @def ELM_DBGLN(str);
 * @param str the string to print
 * @brief The same as ELM_DBG, except it adds a new line character at the end.\n
 * If ELM_NO_DBG is not defined, the alias DBG is available.
 */

/**
 * @ingroup log
 * @def ELM_DBGV(level, str);
 * @param str the string to print
 * @param level bitmask to select the levels of verbose that should enable this debug. If level=0, it will never be printed.
 * @brief Will only output the string str if (level & verbose_level) is non-null, that is, if one of the bits in the bit mask level is set to 1 in the global variable verbose_level.
 */

/**
 * Display prefix of log line, which may include the source path and line number of file, the line number of the log, both or neither
 * @return the string to display
 */
elm::String Debug::debugPrefix(const char* file, int line)
{
	if(flags&(SOURCE_INFO|NUMBERING))
	{
		elm::String rtn = _ << color::Yel() << "["; // opening bracket and setting up color if we are in color mode
		if(flags&SOURCE_INFO) // path of the source that called DBG
		{
			rtn = _ << file << ":" << line;
			if(rtn.length() > srcpath_length)
			{ 	// Source path too long, cut it: "longpath/src/main.cpp" becomes [...ath/src/main.cpp])
				rtn = _ << prefix_color << "[" << "..." << rtn.substring(rtn.length() + 3 - srcpath_length);
			}
			else
			{	// Source path too short, align it with whitespaces: "src/main.cpp" becomes [       src/main.cpp]
				elm::String whitespaces;
				for(unsigned int i = 0, len = rtn.length(); i < srcpath_length - len; i++)
					whitespaces = whitespaces.concat(elm::CString(" "));
				rtn = _ << prefix_color << "[" << whitespaces << rtn;
			}
		}
		if(flags&NUMBERING) // output line numbers
		{
			static int line_nb = 0;
			if(flags&SOURCE_INFO) // if we printed the source info before
				rtn = _ << rtn << "|"; // add a | separator
			rtn = _ << rtn << io::align(io::RIGHT, io::width(6, ++line_nb)); // this auto-adds the necessary whitespaces to have a 6-characters number. 45 becomes "    45" and so on
		}
		return elm::String(_ << rtn << "] " << color::RCol()); // closing bracket of the prefix, and resetting color if need be
	}
	else // no prefix
		return "";
}
} // log
} // elm
