project(test)

set(SRC_LIST httpServer.cpp main.cpp)
add_executable(test ${SRC_LIST})
target_link_libraries(test event)
