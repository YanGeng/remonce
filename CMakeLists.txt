cmake_minimum_required (VERSION 2.5)
project(tony)

# The version number.
set (Main_VERSION_MAJOR 1)
set (Main_VERSION_MINOR 0)

# add the build option
add_definitions("-g")

include_directories("${PROJECT_SOURCE_DIR}/Header")

set(DIRS
	Test
	DbDao
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
