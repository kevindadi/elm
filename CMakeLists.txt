cmake_minimum_required(VERSION 2.6)

project("elm")

if(WIN32 OR WIN64 OR MINGW_LINUX)
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -shared-libgcc")
endif()

# gcc based compiler lack of support by cmake (opposed to VS)
# so need to make some manual adjustment in this case
if(CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
endif (CMAKE_COMPILER_IS_GNUCXX AND (CMAKE_BUILD_TYPE MATCHES Release))

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

add_subdirectory(tools)

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


# handle autodoc
option(AUTODOC "generate auto-documentation" OFF)
find_program(DOXYGEN doxygen)
if((DOXYGEN AND NOT EXISTS autodoc) OR AUTODOC)
	message(STATUS "generating autodoc...")
	execute_process(COMMAND "${DOXYGEN}" OUTPUT_QUIET)
	message(STATUS "autodoc done")
endif()
if(DOXYGEN)
	install(DIRECTORY autodoc DESTINATION "${CMAKE_INSTALL_PREFIX}/share/GEL/")
endif()
unset(AUTODOC CACHE)

