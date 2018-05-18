cmake_minimum_required( VERSION 2.8 )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fabi-version=8" )
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
SET( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${PROJECT_SOURCE_DIR}/3rd_party )
include_directories( /usr/local/include )
link_directories( /usr/local/lib )

MESSAGE( STATUS "operation system is ${CMAKE_SYSTEM}" )

add_subdirectory( tree )
#add_subdirectory( 3rd_party/hiredis )
#add_subdirectory( 3rd_party/hippo )
#
#add_subdirectory( algo )
#add_subdirectory( repo )
#add_subdirectory( protocol )
#add_subdirectory( user )
#add_subdirectory( desk )
#add_subdirectory( match )
#
#
#add_subdirectory( examples )
#add_subdirectory( cds )
#add_subdirectory( server )
#add_subdirectory( client )
#add_subdirectory( 3rd_party/spdlog )
#add_subdirectory( 3rd_party/protobuf )
#add_subdirectory( 3rd_party/tbb )
