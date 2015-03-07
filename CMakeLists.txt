cmake_minimum_required(VERSION 2.6)

project("elm")

if(WIN32 OR WIN64 OR MINGW_LINUX)
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -shared-libgcc")
endif()

# support for prctrl/SET_PTRACER
if(UNIX)
	execute_process(COMMAND uname -v OUTPUT_VARIABLE kernel_version OUTPUT_STRIP_TRAILING_WHITESPACE)
	string(REGEX MATCH "^#[0-9]+-Ubuntu " version "${kernel_version}")
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


# installation level
set(INSTALL_TYPE "all" CACHE STRING "Type of installation (one of all, dev-only, dev, lib, com).")
if(INSTALL_TYPE MATCHES "all")
    set(INSTALL_DEV "yes")
    set(INSTALL_LIB "yes")
    set(INSTALL_BIN "yes")
elseif(INSTALL_TYPE MATCHES "dev")
    set(INSTALL_DEV "yes")
    set(INSTALL_LIB "yes")
elseif(INSTALL_TYPE MATCHES "dev-only")
    set(INSTALL_DEV "yes")
elseif(INSTALL_TYPE MATCHES "lib")
    set(INSTALL_LIB "yes")
elseif(INSTALL_TYPE MATCHES "bin")
    set(INSTALL_LIB "yes")
    set(INSTALL_BIN "yes")
else()
    message(ERROR ": unknown INSTALL_TYPE: ${INSTALL_TYPE}")
endif()


# GCC flags
if(CMAKE_BUILD_TYPE MATCHES Release)
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


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
if(NOT(WIN32) AND NOT(WIN64) AND NOT(APPLE))
	find_package(Threads)
	set(HAS_SOCKET ON CACHE BOOL "sockets are supported")
endif()


# look for GDB
find_program(GDB_PATH gdb)
message(STATUS "GDB_PATH = " ${GDB_PATH})
if(GDB_PATH)
	set(CRASH_HANDLER "GDBCrashHandler::DEFAULT")
	message(STATUS "crash handler is " ${CRASH_HANDLER})
endif(GDB_PATH)


#process subdirectories
add_subdirectory(src)
if(ELM_TEST)
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


# header installation
if(INSTALL_DEV)
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
if(INSTALL_DEV)
	add_custom_target("make-autodoc" ALL DEPENDS "autodoc")
	add_custom_command(
		OUTPUT "autodoc"
		DEPENDS "Doxyfile"
		COMMAND "${DOXYGEN}"	
	)
	install(DIRECTORY autodoc DESTINATION "${CMAKE_INSTALL_PREFIX}/share/Elm/")
endif()

