cmake_minimum_required(VERSION 2.8)

project("elm")

if(WIN32 OR WIN64 OR MINGW_LINUX)
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -shared-libgcc")
endif()

# debugging activated
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -g3")

#set(LIBRARY_OUTPUT_PATH lib/${CMAKE_BUILD_TYPE})

if(MINGW OR WIN32)
set(LIBDIR "bin")
else()
set(LIBDIR "lib")
endif()

# gcc based compiler lack of support by cmake (opposed to VS)
# so need to make some manual adjustment in this case
if (CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
endif (CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))

#IF(MINGW)
#	SET(WIN32 on)
#	SET(CMAKE_FIND_LIBRARY_PREFIXES "lib" "")
#	SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll" ".dll.a" ".a" ".lib")
#ENDIF(MINGW)

#message(STATUS ${source_files})

#check endianness
#not in makefile.am, why here ?
include(TestBigEndian)
TEST_BIG_ENDIAN(BIG_ENDIAN)

# MINGW_LINUX
if(MINGW_LINUX OR MINGW_WIN)
	message(STATUS "here !")
	set(LIBXML2 ${CMAKE_BINARY_DIR}/../site/bin/libxml2.dll)
	set(LIBXML2_INCLUDE_DIR ${CMAKE_BINARY_DIR}/../site/include)
	set(LIBXSLT ${CMAKE_BINARY_DIR}/../site/bin/libxslt.dll)
	set(LIBXSLT_INCLUDE_DIR ${CMAKE_BINARY_DIR}/../site/include)

# Unix
elseif(UNIX OR APPLE)
	find_package(LibXml2 0)
	set(LIBXML2 ${LIBXML2_FOUND})
	find_package(LibXslt 0)
	set(LIBXSLT ${LIBXSLT_FOUND})

# Windows
elseif(WIN32)

find_library(LIBXML2 libxml2 PATHS "${CMAKE_BINARY_DIR}/../libxml2-2.7.7.win32/bin")
get_filename_component(LIBXML2_DIR ${LIBXML2} PATH)
set(LIBXML2_INCLUDE_DIR "${LIBXML2_DIR}/../include" CACHE PATH "path to libxml2 include directory")
include_directories(${LIBXML2_INCLUDE_DIR})

if(LIBXML2)
add_definitions("-DHAS_LIBXML")
endif()

find_library(LIBXSLT libxslt PATHS "${CMAKE_BINARY_DIR}/../libxslt-1.1.26.win32/bin")
get_filename_component(LIBXSLT_DIR ${LIBXSLT} PATH)
set(LIBXSLT_INCLUDE_DIR "${LIBXSLT_DIR}/../include"  CACHE PATH "path to libxslt include directory")
include_directories(${LIBXSLT_INCLUDE_DIR})

endif()


#process subdirectories
add_subdirectory(src)
if(ELM_TEST)
	add_subdirectory(test)
endif()

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
if(UNIX OR APPLE)
set(EXCLUDES ${EXCLUDES} PATTERN "Win*Stream.h" EXCLUDE)
endif()
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
if(UNIX OR APPLE)
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
endif()
	
#once Doxygen path has been searched for
#generation of documentation IF Doxygen has been found
#tried testing for DEFINED DOXYGEN_DIR, doesn't work
if(DOXYGEN AND WIN32)
	message(STATUS "Doxygen found, generation of documentation")
	execute_process(COMMAND "cmd" "/C doxygen Doxyfile")
elseif(DOXYGEN AND UNIX) #not tested
	message(STATUS "Doxygen found, generation of documentation")
	execute_process(COMMAND "bash" "doxygen Doxyfile")
else(DOXYGEN AND WIN32)
	message(WARNING "Doxygen not found, cannot generate documentation")
endif(DOXYGEN AND WIN32)


###########################

# Documentation install
#if(DOXYGEN)
#	install(
#		DIRECTORY autodoc
#		DESTINATION share/Elm/
#	)
#endif(DOXYGEN)

