# $Id$

noinst_PROGRAMS	=	test myplugin.so

test_SOURCES		=\
						test.cc \
						test_avl.cpp \
						test_bitvector.cpp \
						test_dllist.cpp \
						test_file.cpp \
						test_formatter.cpp \
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
test_LDFLAGS		= -rdynamic
test_LDADD			= -L../src -lelm -ldl
test_DEPENDENCIES	= ../src/libelm.a

myplugin_so_SOURCES	= plugin.cpp
myplugin_so_LDFLAGS	= -shared

INCLUDES	= -I../include
AM_CXXFLAGS	= -g3 -fPIC
AM_LDFLAGS =

if HAS_LIBXML
test_SOURCES += test_xom.cpp
AM_CXXFLAGS += @LIBXML_CFLAGS@ -DHAS_LIBXML
AM_LDFLAGS += @LIBXML_LIBS@
endif
	

