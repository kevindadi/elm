#add all headers
file(
	GLOB
	header_dummy
	elm/*.h
	)
#why include xom.h if directory xom is not added ? 

#message(STATUS ${header_dummy})

#including libxml
#including libxslt
find_library(LIBXML libxml2)
find_library(LIBXSLT libxslt)

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
list(APPEND header_files ${LIBXML} ${LIBXSLT})


#checks if all header files are added recursively
#message(STATUS ${header_files})
#checked and valid