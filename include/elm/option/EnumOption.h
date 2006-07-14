/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS
 *
 * elm/option/EnumOption.h -- EnumOption class interface.
 */
#ifndef ELM_OPTION_ENUM_OPTION_H
#define ELM_OPTION_ENUM_OPTION_H

#include <elm/option/StandardOption.h>

namespace elm { namespace option {

// BoolOption class
template <class T>
class EnumOption: public StandardOption {
public:
	typedef struct value_t {
		elm::CString name;
		T value;
	} value_t;
private:
	int val;
	value_t *vals;
	String arg;
public:
	inline EnumOption(Manager& manager, char short_name, CString description,
		value_t values[]);
	inline EnumOption(Manager& manager, CString long_name, CString description,
		value_t values[]);
	inline EnumOption(Manager& manager, char short_name, CString long_name,
		CString description, value_t values[]);
	inline const T& value(void) const;
	inline void set(const T& value);

	// Option overload
	virtual usage_t usage(void);
	virtual CString argDescription(void);
	virtual void process(String arg);
	
	// Operators
	inline operator T(void) const;
	inline EnumOption& operator=(const T& value);
};


// EnumOption inlines
template <class T>
EnumOption<T>::EnumOption(Manager& manager, char short_name, CString description,
value_t values[]): StandardOption(manager, short_name, description),
val(values[0].value), vals(values) {
}

template <class T>
EnumOption<T>::EnumOption(Manager& manager, CString long_name,
CString description, value_t values[]): StandardOption(manager, long_name,
description), val(values[0].value), vals(values) {
}

template <class T>
EnumOption<T>::EnumOption(Manager& manager, char short_name, CString long_name,
CString description, value_t values[]): StandardOption(manager, short_name,
long_name, description), val(values[0].value), vals(values) {
}

template <class T>
inline const T& EnumOption<T>::value(void) const {
	return val;
}

template <class T>
inline void EnumOption<T>::set(const T& value) {
	val = value;
}

template <class T>
usage_t EnumOption<T>::usage(void) {
	return arg_required;
}

template <class T>
CString EnumOption<T>::argDescription(void) {
	return vals[0].name;
}

template <class T>
void EnumOption<T>::process(String arg) {
	for(int i = 1; vals[i].name; i++)
		if(arg == vals[i].name) {
			val = vals[i].value;
			return;
		}
	throw OptionException("bad value \"%s\"", &arg);
}
	
template <class T>
EnumOption<T>::operator T(void) const {
	return val;
}

template <class T>
EnumOption<T>& EnumOption<T>::operator=(const T& value) {
	val = value;
	return *this;
}

} } // elm::option

#endif // ELM_OPTION_ENUM_OPTION_H
