lib_LTLIBRARIES=libelm.la

INCLUDES=-I../include @INCLTDL@

AM_CXXFLAGS = @LIBXML_CFLAGS@

libelm_la_LDFLAGS=-version-info 0:1:0
libelm_la_LIBADD = @LIBLTDL@ @LIBXML_LIBS@
DEFS=@ELM_DEBUG_DEFS@

libelm_la_SOURCES= \
	utility.cpp \
	string_String.cpp \
	string_StringBuffer.cpp \
	io_OutStream.cpp \
	io_UnixOutStream.cpp \
	io_Output.cpp \
	io_InFileStream.cpp \
	io_InStream.cpp \
	io_OutFileStream.cpp \
	io_UnixInStream.cpp \
	io_IOException.cpp \
	block_DynBlock.cpp \
	genstruct_FragTable.cpp \
	genstruct_HashTable.cpp \
	genstruct_SLList.cpp \
	genstruct_VectorQueue.cpp \
	genstruct_Table.cpp \
	inhstruct_SLList.cpp \
	inhstruct_BinTree.cpp \
	inhstruct_SortedBinTree.cpp \
	inhstruct_DLList.cpp \
	inhstruct_AVLTree.cpp \
	option_Option.cpp \
	option_StandardOption.cpp \
	option_BoolOption.cpp \
	option_Manager.cpp \
	option_StringOption.cpp \
	option_ActionOption.cpp \
	Iterator.cpp \
	Collection.cpp \
	util_BitVector.cpp \
	util_test.cpp \
	util_VarArg.cpp \
	io_BlockOutStream.cpp \
	io_BlockInStream.cpp \
	system_Plugin.cpp \
	system_Plugger.cpp \
	system_SystemException.cpp \
	system_Path.cpp \
	system_FileItem.cpp \
	system_File.cpp \
	system_Directory.cpp \
	system_StopWatch.cpp \
	util_Formatter.cpp \
	util_Option.cpp \
	util_Pair.cpp \
	util_Version.cpp

if HAS_LIBXML
libelm_la_SOURCES += \
	xom_Builder.cpp \
	xom_Document.cpp \
	xom_Element.cpp \
	xom_Node.cpp \
	xom_NodeFactory.cpp \
	xom_ParentNode.cpp \
	xom_String.cpp \
	xom_Text.cpp \
	xom_macros.h
endif
