

set(LIBELM_LA_SOURCES
	"concepts.h"
	"doc.h"
	"alloc_BlockAllocator.cpp"
	"alloc_BlockAllocatorWithGC.cpp"
	"alloc_DefaultAllocator.cpp"
	"alloc_StackAllocator.cpp"
	"block_DynBlock.cpp"
	"checksum_Fletcher.cpp"
	"checksum_MD5.cpp"
	"debug.cpp"
	"genstruct.h"
	"genstruct_AssocList.cpp"
	"genstruct_AVLTree.cpp"
	"genstruct_DLList.cpp"
	"genstruct_FragTable.cpp"
	"genstruct_HashTable.cpp"
	"genstruct_SLList.cpp"
	"genstruct_DAGNode.cpp"
	"genstruct_SortedBinMap.cpp"
	"genstruct_SortedBinTree.cpp"
	"genstruct_SortedSLList.cpp"
	"genstruct_Tree.cpp"
	"genstruct_VectorQueue.cpp"
	"genstruct_Table.cpp"
	"genstruct_Tree.cpp"
	"inhstruct_BinTree.cpp"
	"inhstruct_SortedBinTree.cpp"
	"inhstruct_DLList.cpp"
	"inhstruct_SLList.cpp"
	"inhstruct_Tree.cpp"
	"int.cpp"
	"io_BlockInStream.cpp"
	"io_BlockOutStream.cpp"
	"io_BufferedInStream.cpp"
	"io_BufferedOutStream.cpp"
	"io_InFileStream.cpp"
	"io_Input.cpp"
	"io_InStream.cpp"
	"io_IOException.cpp"
	"io_Monitor.cpp"
	"io_OutFileStream.cpp"
	"io_Output.cpp"
	"io_OutStream.cpp"
	"io_RandomAccessStream.cpp"
	"io_UnixInStream.cpp"
	"io_UnixOutStream.cpp"
	"io_WinInStream.cpp"
	"io_WinOutStream.cpp"
	"Iterator.cpp"
	"option_Option.cpp"
	"option_BoolOption.cpp"
	"option_ActionOption.cpp"
	"option_EnumOption.cpp"
	"option_IntOption.cpp"
	"option_ListOption.cpp"
	"option_Manager.cpp"
	"serial_Serializer.cpp"
	"serial_SerialClass.cpp"
	"option_StandardOption.cpp"
	"option_StringList.cpp"
	"option_StringOption.cpp"
	"option_SwitchOption.cpp"
	"serial_TextSerializer.cpp"
	"serial_Unserializer.cpp"
	"option_ValueOption.cpp"
	"serial2_serial.cpp"
	"serial2_TextSerializer.cpp"
	"string_AutoString.cpp"
	"string_String.cpp"
	"string_StringBuffer.cpp"
	"system_File.cpp"
	"system_FileItem.cpp"
	"system_Directory.cpp"
	"system_Path.cpp"
	"system_Plugin.cpp"
	"system_Plugger.cpp"
	"system_Process.cpp"
	"system_ProcessBuilder.cpp"
	"system_StopWatch.cpp"
	"system_System.cpp"
	"system_SystemException.cpp"
	"system_SystemIO.cpp"
	#"system_Thread.cpp"
	"type_info.cpp"
	"util_AutoDestructor.cpp"
	"util_BitVector.cpp"
	"util_Cleaner.cpp"
	"util_Comparator.cpp"
	"util_delegate.cpp"
	"util_Equiv.cpp"
	"util_ErrorHandler.cpp"
	"util_Formatter.cpp"
	"util_HashKey.cpp"
	"util_Initializer.cpp"
	"util_MessageException.cpp"
	"util_Option.cpp"
	"util_Pair.cpp"
	"util_Ref.cpp"
	"util_strong_type.cpp"
	"util_test.cpp"
	"util_VarArg.cpp"
	"util_Version.cpp"
	"utility.cpp"
	)

if(UNIX AND NOT APPLE)
	# be careful: the order of these sources matters for static object initialization
	list(APPEND LIBELM_LA_SOURCES "debug_GDBCrashHandler.cpp" "debug_CrashHandler.cpp")
endif()

if(NOT(WIN32) AND NOT(WIN64))
	list(APPEND LIBELM_LA_SOURCES "net_ClientSocket.cpp" "net_ServerSocket.cpp")
endif()


include_directories("../include")
include_directories(".")
include_directories(${LIBXML2_INCLUDE_DIR})
include_directories(${LIBXSLT_INCLUDE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -g3 -Wall")

if(LIBXML2)
list(APPEND LIBELM_LA_SOURCES
	"serial_XOMUnserializer.cpp"
	"serial2_XOMUnserializer.cpp"
	"serial2_XOMSerializer.cpp"
	"xom_Attribute.cpp"
	"xom_Builder.cpp"
	"xom_Comment.cpp"
	"xom_Document.cpp"
	"xom_Element.cpp"
	"xom_Elements.cpp"
	"xom_Exception.cpp"
	"xom_Node.cpp"
	"xom_NodeFactory.cpp"
	"xom_ParentNode.cpp"
	"xom_Serializer.cpp"
	"xom_String.cpp"
	"xom_Text.cpp"
	"xom_XIncluder.cpp"
	"xom_macros.h")
endif(LIBXML2)
	
#removing OS-special files
#it's hardcoded, havn't found (yet) a better way to do
if(MINGW_LINUX OR WIN32)
	list(REMOVE_ITEM LIBELM_LA_SOURCES io_UnixInStream.cpp)
	list(REMOVE_ITEM LIBELM_LA_SOURCES io_UnixOutStream.cpp)
elseif(UNIX OR APPLE)
	list(REMOVE_ITEM LIBELM_LA_SOURCES io_WinInStream.cpp)
	list(REMOVE_ITEM LIBELM_LA_SOURCES io_WinOutStream.cpp)
endif()

if(LIBXSLT)
list(APPEND LIBELM_LA_SOURCES
	"xom_XSLTransform.cpp"
	)
endif(LIBXSLT)

add_library(elm SHARED ${LIBELM_LA_SOURCES})
if(LIBXML2)
	if(UNIX)
		target_link_libraries(elm ${LIBXML2_LIBRARIES})
		target_link_libraries(elm ${LIBXSLT_LIBRARIES})
	elseif(WIN32)
		target_link_libraries(elm ${LIBXML2})
		target_link_libraries(elm ${LIBXSLT})
	endif(UNIX)
endif(LIBXML2)


# installation
if(MINGW_LINUX OR MINGW_WIN OR UNIX)
	install(TARGETS elm DESTINATION ${LIBDIR})	
elseif(WIN32)
	install(TARGETS elm DESTINATION ${CMAKE_BINARY_DIR})
endif()
