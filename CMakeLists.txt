cmake_minimum_required(VERSION 2.8)

#source files
file(
	GLOB_RECURSE
	source_files
	src/*.cpp
	)

#check endianness
#not in makefile.am, why here ?
include(TestBigEndian)
TEST_BIG_ENDIAN(BIG_ENDIAN)


#process subdirectories
#add_subdirectory(libltdl)
add_subdirectory(src)
#add_subdirectory(test)
add_subdirectory(include)


#adding a library for elm
#add_library(elm SHARED ${source_files} ${header_files})

# build configuration file
configure_file (
  "${PROJECT_SOURCE_DIR}/config.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)

###########################
#adding Doxygen support
if(UNIX AND NOT APPLE)
	#if using a unix system
	message(STATUS "Using Unix system, not MacOS")
	find_path(DOXYGEN_DIR Doxygen
		/usr/local/bin
		/usr/bin
		)
elseif(WIN32)
	#not tested
	message(STATUS "Using Win32 system")
	find_path(DOXYGEN_DIR Doxygen
		PATH
		)
elseif(APPLE)
	#not tested either, and shall not test
	message(WARNING "MacOS not supported")
else(UNIX AND NOT APPLE)
	#in case of some more exotic OS
	message(WARNING "OS not supported")
endif(UNIX AND NOT APPLE)
	
#once Doxygen path has been searched for
#generation of documentation IF Doxygen has been found
#tried testing for DEFINED DOXYGEN_DIR, doesn't work
if(DOXYGEN_DIR)
	message(STATUS "Doxygen found, generation of documentation")
	execute_process(COMMAND mkdir doc
					COMMAND cd doc
					COMMAND ${DOXYGEN_DIR}/doxygen Doxyfile
					)
else(DOXYGEN_DIR)
	message(WARNING "Doxygen not found, cannot generate documentation")
endif(DOXYGEN_DIR)

###########################

# install include
install(DIRECTORY include/elm DESTINATION include
	FILES_MATCHING PATTERN "*.h" PATTERN "CVS" EXCLUDE)
