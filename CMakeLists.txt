project( better )

cmake_minimum_required( VERSION 3.10 )
set(CMAKE_CXX_STANDARD 17)

include_directories( /usr/local/include )
link_directories( /usr/local/lib )


#set( CMAKE_CXX_COMPILER "/usr/local/bin/g++-8" )
#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fabi-version=0" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0" )
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )
include_directories( ${PROJECT_SOURCE_DIR} )
#include_directories( ${PROJECT_SOURCE_DIR}/3rd_party )

message( STATUS "operation system is ${CMAKE_SYSTEM}" )

add_subdirectory( test )
add_subdirectory( benchmark )

