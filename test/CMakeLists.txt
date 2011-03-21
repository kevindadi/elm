

set(TEST_SOURCES
	"test.cc"
	"test_autostr.cpp"
	"test_bitvector.cpp"
	"test_dllist.cpp"
	"test_file.cpp"
	"test_formatter.cpp"
	"test_frag_table.cpp"
	"test_hashkey.cpp"
	"test_hashtable.cpp"
	"test_io_format.cpp"
	"test_io_output.cpp"
	"test_lock.cpp"
	"test_md5.cpp"
	"test_option.cpp"
	"test_plugin.cpp"
	"test_process.cpp"
	"test_ref.cpp"
	"test_sllist.cpp"
	"test_string.cpp"
	"test_string_buffer.cpp"
	"test_table.cpp"
	"test_utility.cpp"
	"test_vararg.cpp"
	"test_vector.cpp"
	"test_vector_queue.cpp"
	"test_sorted_bintree.cpp"
)


include_directories("../include")
include_directories(".")

add_executable(test ${TEST_SOURCES})
target_link_libraries(test elm)
