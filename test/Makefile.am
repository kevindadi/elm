# $Id$

noinst_PROGRAMS	=	test myplugin.so

test_SOURCES		=\
						test.cc \
						test_string_buffer.cpp \
						test_sorted_bintree.cpp \
						test_dllist.cpp \
						test_plugin.cpp \
						test_avl.cpp \
						test_sllist.cpp \
						test_bitvector.cpp \
						test_string.cpp \
						test_utility.cpp \
						test_vector.cpp \
						test_hashtable.cpp \
						test_lock.cpp \
						test_file.cpp \
						test_vararg.cpp \
						test_vector_queue.cpp
test_LDFLAGS		= -rdynamic
test_LDADD			= -L../src -lelm -ldl
test_DEPENDENCIES	= ../src/libelm.a

myplugin_so_SOURCES	= plugin.cpp
myplugin_so_LDFLAGS	= -shared

INCLUDES	= -I../include
AM_CXXFLAGS	= -g3 -fPIC


