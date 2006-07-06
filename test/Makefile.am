# $Id$

noinst_PROGRAMS	=	test
noinst_LTLIBRARIES = myplugin.la

INCLUDES	= -I../include
AM_CXXFLAGS	= -g3
AM_CXXFLAGS += @LIBXML_CFLAGS@ -DHAS_LIBXML


# Test program
test_LDADD			=  -dlopen force ../src/libelm.la
test_DEPENDENCIES	= ../src/libelm.la

test_SOURCES		=\
						test.cc \
						test_avl.cpp \
						test_bitvector.cpp \
						test_dllist.cpp \
						test_file.cpp \
						test_formatter.cpp \
						test_frag_table.cpp \
						test_hashtable.cpp \
						test_io_format.cpp \
						test_lock.cpp \
						test_plugin.cpp \
						test_sllist.cpp \
						test_sorted_bintree.cpp \
						test_string.cpp \
						test_string_buffer.cpp \
						test_table.cpp \
						test_utility.cpp \
						test_vararg.cpp \
						test_vector.cpp \
						test_vector_queue.cpp

if HAS_LIBXML
test_SOURCES += test_xom.cpp
test_LDADD += @LIBXML_LIBS@
endif


# MyPlugin plugin
myplugin_la_LDFLAGS	= -module -rpath @abs_builddir@
myplugin_la_LIBADD = ../src/libelm.la
myplugin_la_DEPS = ../src/libelm.la
myplugin_la_SOURCES	= plugin.cpp
