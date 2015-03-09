set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

aux_source_directory(. dir_DbDao_srcs)
add_library(DbDao SHARED ${dir_DbDao_srcs})
add_library(DbDao_static STATIC ${dir_DbDao_srcs})

set_target_properties(DbDao_static PROPERTIES OUTPUT_NAME "DbDao")
get_target_property(OUTPUT_VALUE hello_static OUTPUT_NAME)

message(STATUS “This is the DbDao_static OUTPUT_NAME:”${OUTPUT_VALUE})

set_target_properties(DbDao PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(DbDao_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(DbDao PROPERTIES VERSION 1.0 SOVERSION 1)
