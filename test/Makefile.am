# $Id$

check_PROGRAMS = \
	serial2 \
	unserial2 \
	test \
	test_assoc_list \
	test_io \
	test_sorted_sllist \
	test_type_info \
	test_tree

all_checks: $(check_PROGRAMS)


# new_avl
noinst_LTLIBRARIES = myplugin.la

INCLUDES	= -I../include
AM_CXXFLAGS = -Wall
if HAS_LIBXML
AM_CXXFLAGS += -DHAS_LIBXML
endif
if IS_SHARED
AM_CXXFLAGS += -DIS_SHARED
endif

# Test program
test_LDADD = -dlopen force -dlopen myplugin.la ../src/libelm.la -lefence
test_DEPENDENCIES = ../src/libelm.la myplugin.la

test_SOURCES		=\
						test.cc \
						test_autostr.cpp \
						test_bitvector.cpp \
						test_dllist.cpp \
						test_file.cpp \
						test_formatter.cpp \
						test_frag_table.cpp \
						test_hashtable.cpp \
						test_io_format.cpp \
						test_io_output.cpp \
						test_lock.cpp \
						test_option.cpp \
						test_plugin.cpp \
						test_process.cpp \
						test_ref.cpp \
						test_sllist.cpp \
						test_string.cpp \
						test_string_buffer.cpp \
						test_table.cpp \
						test_utility.cpp \
						test_vararg.cpp \
						test_vector.cpp \
						test_vector_queue.cpp \
						test_sorted_bintree.cpp

if HAS_LIBXML
test_SOURCES += \
	test_xom.cpp \
	test_serial.cpp
endif


# MyPlugin plugin
myplugin_la_LDFLAGS	= -module -rpath @abs_builddir@
myplugin_la_LIBADD = ../src/libelm.la  -lefence
myplugin_la_DEPS = ../src/libelm.la
myplugin_la_SOURCES	= plugin.cpp


# serial2 program
serial2_LDADD = -dlopen force ../src/libelm.la
serial2_DEPENDENCIES = ../src/libelm.la
serial2_SOURCES		= serial2.cpp

# unserial2 program
unserial2_LDADD = -dlopen force ../src/libelm.la
unserial2_DEPENDENCIES = ../src/libelm.la
unserial2_SOURCES		= unserial2.cpp

# test_tree program
test_tree_LDADD			= ../src/libelm.la
test_tree_DEPENDENCIES	= ../src/libelm.la
test_tree_SOURCES		= test_tree.cpp

# new_avl program
new_avl_LDADD = ../src/libelm.la
new_avl_DEPENDENCIES = ../src/libelm.la
new_avl_SOURCES=new_avl.cpp

# test_sorted_sllist program
test_sorted_sllist_LDADD = ../src/libelm.la
test_sorted_sllist_DEPENDENCIES = ../src/libelm.la
test_sorted_sllist_SOURCES=test_sorted_sllist.cpp

# test_assoc_list program
test_assoc_list_LDADD = ../src/libelm.la
test_assoc_list_DEPENDENCIES = ../src/libelm.la
test_assoc_list_SOURCES=test_assoc_list.cpp

# test_assoc_list program
test_type_info_LDADD = ../src/libelm.la
test_type_info_DEPENDENCIES = ../src/libelm.la
test_type_info_SOURCES=test_type_info.cpp

# test_io program
test_io_LDADD = ../src/libelm.la
test_io_DEPENDENCIES = ../src/libelm.la
test_io_SOURCES=test_io.cpp

TESTS = ./test
