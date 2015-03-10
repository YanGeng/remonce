project(test)
add_definitions(-lstdc++)
set(SRC_LIST netWorkTest.cpp dynServiceFactory.cpp dbService.cpp)
add_executable(test ${SRC_LIST})
