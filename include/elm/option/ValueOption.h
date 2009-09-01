/*
 *	$Id$
 *	ValueOption class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2006-07, IRIT UPS.
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
#ifndef ELM_OPTION_VALUEOPTION_H_
#define ELM_OPTION_VALUEOPTION_H_

#include <elm/option/StandardOption.h>
#include <elm/type_info.h>

namespace elm { namespace option {

// ValueOption<T> class
template <class T>
class ValueOption: public StandardOption {
public:
	ValueOption(
		Manager& manager,
		char short_name,
		CString description,
		CString arg_description,
		const T& value = type_info<T>::null)
	:	StandardOption(manager, short_name, description),
		arg_desc(arg_description),
		val(value) { }
	ValueOption(
		Manager& manager,
		CString long_name,
		CString description,
		CString arg_description,
		const T& value = type_info<T>::null)
	:	StandardOption(manager, long_name, description),
		arg_desc(arg_description),
		val(value) { }
	ValueOption(
		Manager& manager,
		char short_name,
		CString long_name,
		CString description,
		CString arg_description,
		const T& value = type_info<T>::null)
	:	StandardOption(manager, short_name, long_name, description),
		arg_desc(arg_description),
		val(value) { }

	inline const T& get(void) const { return val; };
	inline void set(const T& value) { val = value; };

	// Option overload
	virtual usage_t usage(void) { return arg_required; }
	virtual cstring argDescription(void) { return arg_desc; }

	// Operators
	inline operator const T&(void) const { return get(); };
	inline ValueOption<T>& operator=(const T& value) { set(value); return *this; };
	inline const T& operator*(void) const { return get(); }
	inline operator bool(void) const { return get(); }

	// deprecated
	inline const T& value(void) const { return val; };

private:
	cstring arg_desc;
	T val;
};

} }	// elm::option

#endif /* ELM_OPTION_VALUEOPTION_H_ */
