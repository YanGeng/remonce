project(test) 
add_definitions(-lstdc++)

include_directories("/Users/tony/SandBox/remonce/Header")

set(SRC_LIST xmlConf.cpp xmlConfTest.cpp)
add_executable(test ${SRC_LIST})
target_link_libraries(xml2)
