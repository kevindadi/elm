#add all headers
file(
	GLOB
	header_dummy
	elm/*.h
	)
#why include xom.h if directory xom is not added ? 

#message(STATUS ${header_dummy})

#including libxml
#find_library(LIBXML libxml2)
#including libxslt
#find_library(LIBXSLT libxslt)
#including libtool
#find_library(LIBTOOL ltdl)

#check if gnu debugger is installed
#find_program(GDB_CRASH_HANDLER gdb)
if(GDB_CRASH_HANDLER)
	list(APPEND header_files ${GDB_CRASH_HANDLER})
endif(GDB_CRASH_HANDLER)

file(
	GLOB_RECURSE
	header_files
	elm/alloc/*.h
	elm/block/*.h
	elm/checksum/*.h
	elm/datastruct/*.h
	elm/genstruct/*.h
	elm/inhstruct/*.h
	elm/io/*.h
	elm/option/*.h
	elm/string/*.h
	elm/util/*.h
	elm/serial/*.h
	elm/serial2/*.h
	elm/system/*.h
	)

list(APPEND header_files ${header_dummy})
list(APPEND header_files)


#removing OS-special files
#it's hardcoded, havn't found (yet) a better way to do
if(UNIX AND NOT APPLE AND NOT MINGW)
find_file(WIN1 WinInStream.h PATHS elm/io/)
find_file(WIN2 WinOutStream.h PATHS elm/io/)
list(REMOVE_ITEM header_files ${WIN1})
list(REMOVE_ITEM header_files ${WIN2})
elseif(MINGW OR WIN32)
find_file(UNIX1 UnixInStream.h PATHS elm/io/)
find_file(UNIX2 UnixOutStream.h PATHS elm/io/)
list(REMOVE_ITEM header_files ${UNIX1})
list(REMOVE_ITEM header_files ${UNIX2})
endif(UNIX AND NOT APPLE AND NOT MINGW)

#checks if all header files are added recursively
#message(STATUS ${header_files})
#checked and valid
