set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#aux_source_directory(. dir_netWork_srcs)
set(dir_netWork_srcs dynServiceFactory.cpp 
					dbService.cpp
					httpServer.cpp)
add_library(netWork SHARED ${dir_netWork_srcs})
add_library(netWork_static STATIC ${dir_netWork_srcs})

set_target_properties(netWork_static PROPERTIES OUTPUT_NAME "netWork")
get_target_property(OUTPUT_VALUE hello_static OUTPUT_NAME)

message(STATUS “This is the netWork_static OUTPUT_NAME:”${OUTPUT_VALUE})

set_target_properties(netWork PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(netWork_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(netWork PROPERTIES VERSION 1.0 SOVERSION 1)

target_link_libraries(netWork event)
