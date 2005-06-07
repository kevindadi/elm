SUBDIRS = test_avl test_BitVector test_SLList

noinst_PROGRAMS=test
test_SOURCES=\
	test.cc \
	test_string_buffer.cpp \
	test_sorted_bintree.cpp \
	test_dllist.cpp

test_LDADD=-L../src -lelm
INCLUDES=-I../include
CXXFLAGS=-g3

test_DEPENDENCIES=../src/libelm.a
