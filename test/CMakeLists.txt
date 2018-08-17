set( test_SRCS
        test_binary_indexed_tree.cpp )

add_executable( test0 test0.cpp )
add_executable( testTraits test_traits.cpp )
add_executable( testMT test_mt.cpp )
add_executable( tests ${test_SRCS} )
# target_link_libraries( util tree )