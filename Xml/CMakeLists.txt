#project(test) 
#add_definitions(-lstdc++)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/binTest)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#include_directories("/Users/tony/SandBox/remonce/Header")

set(SRC_LIST xmlConf.cpp xmlConfTest.cpp)
add_executable(xmlTest ${SRC_LIST})
target_link_libraries(xmlTest xml2)
