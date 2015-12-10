/*
 *	$Id$
 *	Debugging, colorful logging tools
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008, IRIT UPS.
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
#ifndef _ELM_LOG_H
#define _ELM_LOG_H

#include <ostream> // std::ostream
#include <elm/io/Output.h>
#include <elm/string/CString.h>
#include <elm/string/AutoString.h>

namespace elm
{
	namespace log
	{
		extern int flags;
		extern int verbose_level;
		extern int srcpath_length; // should be > 3
		enum // debug flags
		{
			DEBUG=		  1 << 0, // print any debugs at all
			SOURCE_INFO=  1 << 1, // show source file and line info prefix
			NUMBERING=	  1 << 2, // number debug outputs
			COLOR=		  1 << 3, // use colors
			COLORS=COLOR,
			ALL=		  0b11111111, // everything
		};
	} // log namespace

	namespace color
	{
		class Color
		{
		public:
			Color(const elm::CString& str) : _str(str) { }
			inline elm::CString operator()() const // Red()
				{ return (log::flags&log::COLOR) ? _str : ""; }
			inline operator elm::CString() const // (CString)Red
				{ return (*this)(); }
			inline operator const char*() const // (const char*)Red
				{ return (*this)().chars(); }
			friend inline elm::io::Output& operator<<(elm::io::Output& out, const Color& color) // elm::cout << Red
				{ return (out << color()); }
			friend inline std::ostream& operator<<(std::ostream& out, const Color& color) // std::cout << Red
				{ return out << color().chars(); }
		private:
			elm::CString _str;
		}; // Color class

		//			Regular			 Bold              Underline         High Intensity    Bold+High Intens.  Background        High Intens. Background         
		const Color Bla("\e[0;30m"), BBla("\e[1;30m"), UBla("\e[4;30m"), IBla("\e[0;90m"), BIBla("\e[1;90m"), On_Bla("\e[40m"), On_IBla("\e[0;100m");
		const Color Red("\e[0;31m"), BRed("\e[1;31m"), URed("\e[4;31m"), IRed("\e[0;91m"), BIRed("\e[1;91m"), On_Red("\e[41m"), On_IRed("\e[0;101m");
		const Color Gre("\e[0;32m"), BGre("\e[1;32m"), UGre("\e[4;32m"), IGre("\e[0;92m"), BIGre("\e[1;92m"), On_Gre("\e[42m"), On_IGre("\e[0;102m");
		const Color Yel("\e[0;33m"), BYel("\e[1;33m"), UYel("\e[4;33m"), IYel("\e[0;93m"), BIYel("\e[1;93m"), On_Yel("\e[43m"), On_IYel("\e[0;103m");
		const Color Blu("\e[0;34m"), BBlu("\e[1;34m"), UBlu("\e[4;34m"), IBlu("\e[0;94m"), BIBlu("\e[1;94m"), On_Blu("\e[44m"), On_IBlu("\e[0;104m");
		const Color Pur("\e[0;35m"), BPur("\e[1;35m"), UPur("\e[4;35m"), IPur("\e[0;95m"), BIPur("\e[1;95m"), On_Pur("\e[45m"), On_IPur("\e[0;105m");
		const Color Cya("\e[0;36m"), BCya("\e[1;36m"), UCya("\e[4;36m"), ICya("\e[0;96m"), BICya("\e[1;96m"), On_Cya("\e[46m"), On_ICya("\e[0;106m");
		const Color Whi("\e[0;37m"), BWhi("\e[1;37m"), UWhi("\e[4;37m"), IWhi("\e[0;97m"), BIWhi("\e[1;97m"), On_Whi("\e[47m"), On_IWhi("\e[0;107m");

		const Color RCol("\e[0m"); 	  // Reset colors
		const Color Bold("\e[1m"); 	  // Switch bold text ON
		const Color Dim("\e[2m"); 	  // Switch darker text ON
		const Color NoBold("\e[21m"); // Switch bold text OFF
		const Color NoDim("\e[22m");  // Switch darker text OFF
		// No support for Blink (\e[5m) as it is deprecated
	} // color namespace
	namespace log
	{
		class Debug {
		public:
			static elm::String debugPrefix(const char* file, int line);
		}; // Debug class
	} // log namespace
} // elm namespace

#define ELM_DBG(str)   { if(elm::log::flags&elm::log::DEBUG) elm::cout << elm::log::Debug::debugPrefix(__FILE__, __LINE__) << str << elm::color::RCol(); } // standard debug
#define ELM_DBGLN(str) { if(elm::log::flags&elm::log::DEBUG) elm::cout << elm::log::Debug::debugPrefix(__FILE__, __LINE__) << str << elm::color::RCol() << elm::io::endl; } // debug with new line
#define ELM_DBGV(level, str) { if(level & elm::log::verbose_level) ELM_DBG(str); } // verbose debug

// aliases
#ifndef ELM_NO_DBG
	#define DBG ELM_DBG
	#define DBGLN ELM_DBGLN
	#define DBGV ELM_DBG
#endif

#endif
