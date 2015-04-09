set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#aux_source_directory(. dir_DbDao_srcs)
set(jsonConvert_srcs JsonConvert.cpp)
add_library(jsonConvert SHARED ${jsonConvert_srcs})
add_library(jsonConvert_static STATIC ${jsonConvert_srcs})

set_target_properties(jsonConvert_static PROPERTIES OUTPUT_NAME "jsonConvert")
get_target_property(OUTPUT_VALUE jsonConvert_static OUTPUT_NAME)

message(STATUS “This is the jsonConvert_static OUTPUT_NAME:”${OUTPUT_VALUE})

set_target_properties(jsonConvert PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(jsonConvert_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(jsonConvert PROPERTIES VERSION 1.0 SOVERSION 1)

#target_link_libraries(jsonConvert boost)
