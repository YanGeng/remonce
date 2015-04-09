cmake_minimum_required (VERSION 2.5)
project(tony)

# The version number.
set (Main_VERSION_MAJOR 1)
set (Main_VERSION_MINOR 0)

# add the build option
add_definitions(-g -lstdc++)

include_directories("${PROJECT_SOURCE_DIR}/Header")

set(DIRS
#	DbDao
	NetWork
	Xml
#	Json
	Test
)

# add all the dirs to the include_directories
foreach(dir ${DIRS})
	include_directories("${PROJECT_SOURCE_DIR}/${dir}")
endforeach()

# add link lib and lib_dir
#link_directories();
#target_link_libraries(mysqlcppconn)

# add all the dirs to the subdirectory
foreach(dir ${DIRS})
	add_subdirectory(${dir})
endforeach()


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(SRC_LIST main.cpp)
add_executable(tony ${SRC_LIST})
target_link_libraries(tony netWork event)
