#SUBDIRS = test_avl test_BitVector test_SLList

noinst_PROGRAMS	=	test

test_SOURCES		=\
						test.cc \
						test_string_buffer.cpp \
						test_sorted_bintree.cpp \
						test_dllist.cpp \
						test_plugin.cpp
test_LDFLAGS		= -rdynamic
test_LDADD			= -L../src -lelm -ldl
test_DEPENDENCIES	= ../src/libelm.a

pkglib_LTLIBRARIES			= myplugin.la
myplugin_la_SOURCES			= plugin.cpp
#myplugin_la_LIBADD			= -L../src -lelm
myplugin_la_LDFLAGS			= -module -export-dynamic
myplugin_la_DEPENDENCIES	= ../src/libelm.a

INCLUDES	= -I../include
AM_CXXFLAGS	= -g3

