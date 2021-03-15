cmake_minimum_required(VERSION 2.8.12)

project("elm")

#add_compile_options(-Wall -Werror)

if(ELM_STAT)
	message(STATUS "ELM_STAT enabled")
else()
	message(STATUS "ELM_STAT disabled")
endif()

if(WIN32 OR WIN64 OR MINGW_LINUX)
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -shared-libgcc")
endif()

# support for prctrl/SET_PTRACER
if(UNIX)
	execute_process(COMMAND uname -v OUTPUT_VARIABLE kernel_version OUTPUT_STRIP_TRAILING_WHITESPACE)
	string(REGEX MATCH "^#[0-9]+.*-Ubuntu " version "${kernel_version}")
	if("${version}" STREQUAL "")
		set(SET_PTRACER no)
	else()
		string(SUBSTRING "${version}" 1 -1 version)
		string(FIND "${version}" "-"  i)
		string(SUBSTRING "${version}" 0 ${i} version)
		if("${version}" EQUAL 29 OR "${version}" GREATER 29)
			set(SET_PTRACER yes)
		else()
			set(SET_PTRACER no)
		endif()
	endif()
	message(STATUS "SET_PTRACER = ${SET_PTRACER}")
	set(SET_PTRACER ${SET_PTRACER} CACHE BOOL "prctrl/SET_PTRACER available")
endif()


# support for int compatibility
include(CheckTypeSize)

CHECK_TYPE_SIZE(int INT_SIZE)
if("${INT_SIZE}" EQUAL 4)
	set(TYPE_INT16 "short")
	set(TYPE_INT32 "int")
elseif("${INT_SIZE}" EQUAL 2)
	set(TYPE_INT16 "int")
	set(TYPE_INT32 "long")
else()
	message(FATAL_ERROR "unsuported int size: ${INT_SIZE}")
endif()

CHECK_TYPE_SIZE(long LONG_SIZE)
if("${LONG_SIZE}" EQUAL 4)
	set(TYPE_INT64 "long long")
elseif("${LONG_SIZE}" EQUAL 8)
	set(TYPE_INT64 "long")
else()
	message(FATAL_ERROR "unsuported long size: ${LONG_SIZE}")
endif()

CHECK_TYPE_SIZE("void *" ADDR_SIZE)
if("${ADDR_SIZE}" EQUAL 2)
	set(ADDR_TYPE "uint16")
elseif("${ADDR_SIZE}" EQUAL 4)
	set(ADDR_TYPE "uint32")
elseif("${ADDR_SIZE}" EQUAL 8)
	set(ADDR_TYPE "uint64")
else()
	message(FATAL_ERROR "unsuported address size: ${ADDR_SIZE}")
endif()


# endianness
include(TestBigEndian)
if(IS_BIG_ENDIAN)
	set(ELM_LITTLE_ENDIAN OFF)
else()
	set(ELM_LITTLE_ENDIAN ON)
endif()


# installation level
set(INSTALL_TYPE "bin,lib,inc,doc" CACHE STRING "Type of installation (a ',' separated combination of bin, lib, inc, doc).")
set(INSTALL_BIN ON)
set(INSTALL_LIB ON)
set(INSTALL_INC ON)
set(INSTALL_DOC OFF)
if(INSTALL_TYPE)
	if(INSTALL_TYPE MATCHES "all")
		set(INSTALL_DOC ON)	
	else()
		if(NOT INSTALL_TYPE MATCHES ".*bin.*")
			set(INSTALL_BIN OFF)
		endif()
		if(NOT INSTALL_TYPE MATCHES ".*lib.*")
			set(INSTALL_LIB OFF)
		endif()
		if(NOT INSTALL_TYPE MATCHES ".*inc.*")
			set(INSTALL_INC OFF)
		endif()
		if(INSTALL_TYPE MATCHES ".*doc.*")
			set(INSTALL_DOC ON)
		endif()
	endif()
endif()


# C++ flags
if(CMAKE_BUILD_TYPE MATCHES Release)
	add_definitions(-DNDEBUG)
endif()
add_compile_options(-Wall)
if(CMAKE_VERSION LESS "3.1")
	add_compile_options(--std=c++11)
else()
	set(CMAKE_CXX_STANDARD 11)
endif()


# libraries libxml2 and libxslt
if(LIBXML2)
	find_package(PackageHandleStandardArgs 0)
	if(WIN32 OR WIN64)
		set(LIBDIR "bin")
	else()
		set(LIBDIR "lib")
	endif()
	find_library(LIBXML2_LIBRARIES NAMES xml2 libxml2 HINTS "${LIBXML2}/${LIBDIR}")
	find_path(LIBXML2_INCLUDE_DIR NAMES libxml/xpath.h HINTS "${LIBXML2}/include")
	FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibXml2 DEFAULT_MSG LIBXML2_LIBRARIES LIBXML2_INCLUDE_DIR)
	find_library(LIBXSLT_LIBRARIES NAMES xslt libxslt HINTS "${LIBXML2}/${LIBDIR}")
	find_path(LIBXSLT_INCLUDE_DIR NAMES libxslt/xslt.h HINTS "${LIBXML2}/include")
	FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibXslt DEFAULT_MSG LIBXSLT_LIBRARIES LIBXSLT_INCLUDE_DIR)
else()
	find_package(LibXml2 0)
	set(LIBXML2 ${LIBXML2_FOUND})
	find_package(LibXslt 0)
	set(LIBXSLT ${LIBXSLT_FOUND})
endif()


# check for thread and socket
if(NOT(WIN32) AND NOT(WIN64))
	find_package(Threads)
	set(HAS_SOCKET ON CACHE BOOL "sockets are supported")
endif()


# look for GDB
find_program(GDB_PATH gdb)
message(STATUS "GDB_PATH = " ${GDB_PATH})
if(GDB_PATH AND UNIX AND NOT WIN32 AND NOT WIN64)
	set(CRASH_HANDLER "GDBCrashHandler::DEFAULT")
else()
	set(CRASH_HANDLER "CrashHandler::DEFAULT")
endif()
message(STATUS "crash handler is " ${CRASH_HANDLER})


#process subdirectories
add_subdirectory(src)
if(WITH_TEST)
	add_subdirectory(test)
endif()

if(INSTALL_BIN)
    add_subdirectory(tools)
endif()


# build configuration file
configure_file (
  "${PROJECT_SOURCE_DIR}/config.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)
configure_file (
  "${PROJECT_SOURCE_DIR}/include/elm/arch.in"
  "${PROJECT_SOURCE_DIR}/include/elm/arch.h"
)


# header installation
if(INSTALL_INC)
	set(EXCLUDES PATTERN "CVS" EXCLUDE)
	if(UNIX OR APPLE)
		set(EXCLUDES ${EXCLUDES} PATTERN "Win*Stream.h" EXCLUDE)
	endif()
	if(WIN32 OR WIN64 OR MINGW)
		set(EXCLUDES ${EXCLUDES} PATTERN "GDBCrashHandler.h" EXCLUDE)
	endif()
	if(NOT LIBXML2)
		set(EXCLUDES ${EXCLUDES} PATTERN "elm/xom/*.h" EXCLUDE)
		set(EXCLUDES ${EXCLUDES} PATTERN "elm/xom.h" EXCLUDE)
	endif()
	install(
		DIRECTORY include/
		DESTINATION include
		FILES_MATCHING PATTERN "*.h"
		${EXCLUDES}
	)
endif()


# handle autodoc
find_program(DOXYGEN doxygen)
if(DOXYGEN)
	add_custom_target("autodoc"
		COMMAND "${DOXYGEN}"
		COMMENT "Building automatic documentation"
		SOURCES "Doxyfile" "${SOURCES}" "src/doc.h"
	)
	if(INSTALL_DOC)
		message(STATUS "install doc: ${INSTALL_DOC}")
		add_custom_target("install-autodoc" ALL DEPENDS "autodoc")
		install(DIRECTORY autodoc DESTINATION "${CMAKE_INSTALL_PREFIX}/share/Elm/")
	endif()
endif()
