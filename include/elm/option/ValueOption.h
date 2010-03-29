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

// AbstractValueOption class
class AbstractValueOption: public Option {
public:
	inline AbstractValueOption(void): use(arg_required) { }
	AbstractValueOption(Manager& man, int tag, ...);
	AbstractValueOption(Manager& man, int tag, VarArg& args);

	// Option overload
	virtual cstring description(void);
	virtual usage_t usage(void);
	virtual cstring argDescription(void);

protected:
	virtual void configure(Manager& manager, int tag, VarArg& args);

private:
	cstring desc, arg_desc;
	usage_t use;
};


// useful inline
template <class T>
inline T read(string arg) { T val; arg >> val; return val; }


// ValueOption<T> class
template <class T>
class ValueOption: public AbstractValueOption {
public:
	inline ValueOption(void) { }

	inline ValueOption(Manager& man, int tag ...)
		{ VARARG_BEGIN(args, tag) AbstractValueOption::init(man, tag, args); VARARG_END }

	inline ValueOption(Manager& man, int tag, VarArg& args)
		{ AbstractValueOption::init(man, tag, args); }

	inline ValueOption(Manager& man, char s, cstring desc, cstring adesc, const T& val = type_info<T>::null)
		{ init(man, short_cmd, s, option::description, &desc, option::arg_desc, &adesc, def, val, end); }

	inline ValueOption(Manager& man, cstring l, cstring desc, cstring adesc, const T& val = type_info<T>::null)
		{ init(man, long_cmd, &l, option::description, &desc, option::arg_desc, &adesc, def, val, end); }

	inline ValueOption(Manager& man, char s, cstring l, cstring desc, cstring adesc, const T& val = type_info<T>::null)
		{ init(man, short_cmd, s, long_cmd, &l, option::description, &desc, option::arg_desc, &adesc, def, val, end); }

	inline const T& get(void) const { return val; };
	inline void set(const T& value) { val = value; };

	// Operators
	inline operator const T&(void) const { return get(); };
	inline ValueOption<T>& operator=(const T& value) { set(value); return *this; };
	inline const T& operator*(void) const { return get(); }
	inline operator bool(void) const { return get(); }

	// Option overload
	virtual void process(String arg) { val = read<T>(arg); }

	// deprecated
	inline const T& value(void) const { return val; };

protected:
	virtual void configure(Manager& manager, int tag, VarArg& args) {
		switch(tag) {
		case def: val = get(args); break;
		default: AbstractValueOption::configure(manager, tag, args);
		}
	}

private:
	T val;
	inline T get(VarArg& args) { return args.next<T>(); }
};

// string specialization
template <>
inline ValueOption<string>::ValueOption(Manager& man, char s, cstring desc, cstring adesc, const string& value)
	{ AbstractValueOption::init(man, short_cmd, s, option::description, &desc, option::arg_desc, &adesc, def, value.chars(), end); }

template <>
inline ValueOption<string>::ValueOption(Manager& man, cstring l, cstring desc, cstring adesc, const string& val)
	{ init(man, long_cmd, &l, option::description, &desc, option::arg_desc, &adesc, def, &val, end); }

template <>
inline ValueOption<string>::ValueOption(Manager& man, char s, cstring l, cstring desc, cstring adesc, const string& val)
	{ init(man, short_cmd, s, long_cmd, &l, option::description, &desc, option::arg_desc, &adesc, def, &val, end); }


// get specialization
template <> inline string ValueOption<string>::get(VarArg& args) { return args.next<const char *>(); }


// read specializations
template <> inline string read<string>(string arg) { return arg; }

} }	// elm::option

#endif /* ELM_OPTION_VALUEOPTION_H_ */
