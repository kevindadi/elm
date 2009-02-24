lib_LTLIBRARIES=libelm.la

INCLUDES=-I../include @INCLTDL@

AM_CXXFLAGS = @LIBXML_CFLAGS@ -Wall

libelm_la_LDFLAGS=-version-info 0:1:0
libelm_la_LIBADD = @LIBLTDL@
if HAS_LIBXML
libelm_la_LIBADD += @LIBXML_LIBS@
endif

DEFS=@ELM_DEBUG_DEFS@

libelm_la_SOURCES= \
	concepts.h \
	doc.h \
	block_DynBlock.cpp \
	debug.cpp \
	debug_CrashHandler.cpp \
	checksum_Fletcher.cpp \
	genstruct.h \
	genstruct_AssocList.cpp \
	genstruct_AVLTree.cpp \
	genstruct_DLList.cpp \
	genstruct_FragTable.cpp \
	genstruct_HashTable.cpp \
	genstruct_SLList.cpp \
	genstruct_DAGNode.cpp \
	genstruct_SortedBinMap.cpp \
	genstruct_SortedBinTree.cpp \
	genstruct_SortedSLList.cpp \
	genstruct_Tree.cpp \
	genstruct_VectorQueue.cpp \
	genstruct_Table.cpp \
	genstruct_Tree.cpp \
	inhstruct_BinTree.cpp \
	inhstruct_SortedBinTree.cpp \
	inhstruct_DLList.cpp \
	inhstruct_SLList.cpp \
	inhstruct_Tree.cpp \
	io_BlockInStream.cpp \
	io_BlockOutStream.cpp \
	io_BufferedInStream.cpp \
	io_InFileStream.cpp \
	io_Input.cpp \
	io_InStream.cpp \
	io_IOException.cpp \
	io_OutFileStream.cpp \
	io_Output.cpp \
	io_OutStream.cpp \
	io_RandomAccessStream.cpp \
	io_UnixInStream.cpp \
	io_UnixOutStream.cpp \
	Iterator.cpp \
	option_Option.cpp \
	option_StandardOption.cpp \
	option_BoolOption.cpp \
	option_Manager.cpp \
	option_StringOption.cpp \
	option_ActionOption.cpp \
	option_EnumOption.cpp \
	option_IntOption.cpp \
	serial_Serializer.cpp \
	serial_SerialClass.cpp \
	serial_TextSerializer.cpp \
	serial_Unserializer.cpp \
	serial_XOMUnserializer.cpp \
	serial2_serial.cpp \
	serial2_TextSerializer.cpp \
	serial2_XOMUnserializer.cpp \
	serial2_XOMSerializer.cpp \
	string_AutoString.cpp \
	string_String.cpp \
	string_StringBuffer.cpp \
	system_File.cpp \
	system_FileItem.cpp \
	system_Directory.cpp \
	system_Path.cpp \
	system_Plugin.cpp \
	system_Plugger.cpp \
	system_Process.cpp \
	system_ProcessBuilder.cpp \
	system_StopWatch.cpp \
	system_System.cpp \
	system_SystemException.cpp \
	system_SystemIO.cpp \
	type_info.cpp \
	util_AutoDestructor.cpp \
	util_BitVector.cpp \
	util_Cleaner.cpp \
	util_Comparator.cpp \
	util_delegate.cpp \
	util_Equiv.cpp \
	util_Formatter.cpp \
	util_HashKey.cpp \
	util_Initializer.cpp \
	util_MessageException.cpp \
	util_Option.cpp \
	util_Pair.cpp \
	util_Ref.cpp \
	util_strong_type.cpp \
	util_test.cpp \
	util_VarArg.cpp \
	util_Version.cpp \
	utility.cpp

#	inhstruct_AVLTree.cpp


if HAS_LIBXML
libelm_la_SOURCES += \
	xom_Attribute.cpp \
	xom_Builder.cpp \
	xom_Document.cpp \
	xom_Element.cpp \
	xom_Elements.cpp \
	xom_Exception.cpp \
	xom_Node.cpp \
	xom_NodeFactory.cpp \
	xom_ParentNode.cpp \
	xom_Serializer.cpp \
	xom_String.cpp \
	xom_Text.cpp \
	xom_XIncluder.cpp \
	xom_macros.h
endif

if HAVE_GDB_CRASH_HANDLER
libelm_la_SOURCES += debug_GDBCrashHandler.cpp
endif
