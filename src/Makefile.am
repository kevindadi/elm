lib_LIBRARIES=libelm.a
libelm_a_SOURCES= \
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
	genstruct_HashTable.cpp \
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
	util_Version.cpp

INCLUDES=-I../include
AM_CXXFLAGS=-g3
DEFS=@ELM_DEBUG_DEFS@

if HAS_LIBXML
libelm_a_SOURCES += \
	xom_Builder.cpp \
	xom_Document.cpp \
	xom_Element.cpp \
	xom_Node.cpp \
	xom_NodeFactory.cpp \
	xom_ParentNode.cpp \
	xom_String.cpp \
	xom_macros.h
AM_CXXFLAGS+= @LIBXML_CFLAGS@
endif
	
