/*
 *	test for ANSI codes
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
#include <elm/test.h>

using namespace elm;

TEST_BEGIN(ansi)

	cout << io::BOLD << "bold text" << io::PLAIN << io::endl;
	cout << io::FAINT << "faint text" << io::PLAIN << io::endl;
	cout << io::ITALIC << "italic text" << io::PLAIN << io::endl;
	cout << io::UNDERLINE << "underline text" << io::PLAIN << io::endl;
	cout << io::BLINK << "blink text" << io::PLAIN << io::endl;
	cout << io::RAPID_BLINK << "rapid blink text" << io::PLAIN << io::endl;
	cout << io::REVERSE << "reverse mode text" << io::PLAIN << io::endl;

	cout << io::BLACK << "black text" << io::PLAIN << io::endl;
	cout << io::RED << "red text" << io::PLAIN << io::endl;
	cout << io::GREEN << "green text" << io::PLAIN << io::endl;
	cout << io::YELLOW << "yellow text" << io::PLAIN << io::endl;
	cout << io::BLUE << "blue text" << io::PLAIN << io::endl;
	cout << io::MAGENTA << "magenta text" << io::PLAIN << io::endl;
	cout << io::CYAN << "cyan text" << io::PLAIN << io::endl;
	cout << io::WHITE << "white text" << io::PLAIN << io::endl;

	cout << io::BRIGHT_BLACK << "bright black text" << io::PLAIN << io::endl;
	cout << io::BRIGHT_RED << "bright red text" << io::PLAIN << io::endl;
	cout << io::BRIGHT_GREEN << "bright green text" << io::PLAIN << io::endl;
	cout << io::BRIGHT_YELLOW << "bright yellow text" << io::PLAIN << io::endl;
	cout << io::BRIGHT_BLUE << "bright blue text" << io::PLAIN << io::endl;
	cout << io::BRIGHT_MAGENTA << "bright magenta text" << io::PLAIN << io::endl;
	cout << io::BRIGHT_CYAN << "bright cyan text" << io::PLAIN << io::endl;
	cout << io::BRIGHT_WHITE << "bright white text" << io::PLAIN << io::endl;

	cout << io::BACK_BLACK << "black back" << io::PLAIN << io::endl;
	cout << io::BACK_RED << "red back" << io::PLAIN << io::endl;
	cout << io::BACK_GREEN << "green back" << io::PLAIN << io::endl;
	cout << io::BACK_YELLOW << "yellow back" << io::PLAIN << io::endl;
	cout << io::BACK_BLUE << "blue back" << io::PLAIN << io::endl;
	cout << io::BACK_MAGENTA << "magenta back" << io::PLAIN << io::endl;
	cout << io::BACK_CYAN << "cyan back" << io::PLAIN << io::endl;
	cout << io::BACK_WHITE << "white back" << io::PLAIN << io::endl;

	cout << io::BACK_BRIGHT_BLACK << "bright black back" << io::PLAIN << io::endl;
	cout << io::BACK_BRIGHT_RED << "bright red back" << io::PLAIN << io::endl;
	cout << io::BACK_BRIGHT_GREEN << "bright green back" << io::PLAIN << io::endl;
	cout << io::BACK_BRIGHT_YELLOW << "bright yellow back" << io::PLAIN << io::endl;
	cout << io::BACK_BRIGHT_BLUE << "bright blue back" << io::PLAIN << io::endl;
	cout << io::BACK_BRIGHT_MAGENTA << "bright magenta back" << io::PLAIN << io::endl;
	cout << io::BACK_BRIGHT_CYAN << "bright cyan back" << io::PLAIN << io::endl;
	cout << io::BACK_BRIGHT_WHITE << "bright white back" << io::PLAIN << io::endl;

TEST_END
