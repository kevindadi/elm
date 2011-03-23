cmake_minimum_required(VERSION 2.8)

project("elm")


set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})


# gcc based compiler lack of support by cmake (opposed to VS)
# so need to make some manual adjustment in this case
if (CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
endif (CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))


#message(STATUS ${source_files})

#check endianness
#not in makefile.am, why here ?
include(TestBigEndian)
TEST_BIG_ENDIAN(BIG_ENDIAN)

# Unix
if(UNIX)
#include(LibXml2)
find_package(LibXml2 0)

# Windows
elseif(WIN32 OR MINGW)
#message(WARNING "LIBXML_INCLUDE_DIR is to be set to the include directory, not the libxml directory for OS compatibility issues")
#find_path(LIBXML_INCLUDE_DIR "get_include_dir")
#include_directories(BEFORE ${LIBXML_INCLUDE_DIR})
set(LIBXML2_LIBRARIES ${CMAKE_BINARY_DIR}/../libxml2-2.7.7.win32/lib/libxml2.lib)
#message(STATUS ${LIBXML2_LIBRARIES})
set(LIBXML2_INCLUDE_DIR ${CMAKE_BINARY_DIR}/../libxml2-2.7.7.win32/include/)
find_package(LibXml2 0)

set(LIBXSLT_LIBRARIES ${CMAKE_BINARY_DIR}/../libxslt-1.1.26.win32/lib/libxslt.lib)
set(LIBXSLT_INCLUDE_DIR ${CMAKE_BINARY_DIR}/../libxslt-1.1.26.win32/include/)
find_package(LibXslt 0)
endif(UNIX)


#process subdirectories
add_subdirectory(src)
add_subdirectory(test)

# look for GDB
find_program(GDB_PATH gdb)
message(STATUS "GDB_PATH = " ${GDB_PATH})
if(GDB_PATH)
set(CRASH_HANDLER "GDBCrashHandler::DEFAULT")
message(STATUS "crash handler is " ${CRASH_HANDLER})
endif(GDB_PATH)

# build configuration file
configure_file (
  "${PROJECT_SOURCE_DIR}/config.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)


# header installation
set(EXCLUDES PATTERN "CVS" EXCLUDE)
if(UNIX)
set(EXCLUDES ${EXCLUDES} PATTERN "Win*Stream.h" EXCLUDE)
endif(UNIX)
if(WIN32 OR MINGW)
set(EXCLUDES ${EXCLUDES} PATTERN "GDBCrashHandler.h" EXCLUDE)
endif(WIN32 OR MINGW)
if(LIBXML2-NOTFOUND)
set(EXCLUDES ${EXCLUDES} PATTERN "elm/xom.h" "elm/xom/*.h" EXCLUDE)
endif(LIBXML2-NOTFOUND)

install(
	DIRECTORY include/
	DESTINATION include
	FILES_MATCHING PATTERN "*.h"
	${EXCLUDES}
)

###########################
#adding Doxygen support
if(UNIX AND NOT APPLE)
	#if using a unix system
	message(STATUS "Using Unix system, not MacOS")
	find_program(DOXYGEN doxygen
		/usr/local/bin
		/usr/bin
		)
elseif(WIN32 OR MINGW)
	#not tested
	message(STATUS "Using Win32 system")
	find_program(DOXYGEN doxygen
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
if(DOXYGEN)
	message(STATUS "Doxygen found, generation of documentation")
	execute_process(COMMAND "doxygen Doxyfile")
else(DOXYGEN)
	message(WARNING "Doxygen not found, cannot generate documentation")
endif(DOXYGEN)

###########################

# Documentation install
if(DOXYGEN)
	install(
		DIRECTORY autodoc
		DESTINATION share/Elm/
	)
endif(DOXYGEN)

