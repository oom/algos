project( algos )

if( COMMAND cmake_policy )
   cmake_policy( SET CMP0000 OLD ) # do not require cmake_minumum_required
   cmake_policy( SET CMP0002 NEW )
   cmake_policy( SET CMP0003 NEW )
   cmake_policy( SET CMP0011 NEW )
endif(COMMAND cmake_policy)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wno-long-long -pipe -g -pedantic" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2" )

macro( algos_add_executable _name )
   include_directories( ${common_SOURCE_DIR} )
   link_directories( ${common_BINARY_DIR} )

   add_executable( ${_name} ${ARGN} )
   target_link_libraries( ${_name} common )
endmacro( algos_add_executable _name )

add_subdirectory( common )
add_subdirectory( array )
add_subdirectory( queue_stack )
add_subdirectory( dp )
