set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

aux_source_directory(. dir_DbDao_srcs)
add_library(dbDao SHARED ${dir_DbDao_srcs})
add_library(dbDao_static STATIC ${dir_DbDao_srcs})

set_target_properties(dbDao_static PROPERTIES OUTPUT_NAME "dbDao")
get_target_property(OUTPUT_VALUE hello_static OUTPUT_NAME)

message(STATUS “This is the dbDao_static OUTPUT_NAME:”${OUTPUT_VALUE})

set_target_properties(dbDao PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(dbDao_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(dbDao PROPERTIES VERSION 1.0 SOVERSION 1)
