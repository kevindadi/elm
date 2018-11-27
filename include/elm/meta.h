/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * Meta-programming definitions.
 */
#ifndef ELM_META_H
#define ELM_META_H


namespace elm {

// Value pattern
template <int x> struct _n { enum { _ = x }; };
struct _true { enum { _ = 1 }; };
struct _false { enum { _ = 0 }; };

// If pattern
template <bool c, class T, class E> struct _if: public T {  };
template <class T, class E> struct _if<false, T, E>: public E {  };

}	// elm

#endif // ELM_META_H

