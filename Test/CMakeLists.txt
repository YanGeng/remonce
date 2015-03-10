set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/binTest)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#add_executable(cFuncTest cFuncTest.cpp)
add_executable(netWorkTest netWorkTest.cpp)

# add link lib and lib_dir
#link_directories();
#target_link_libraries(cFuncTest mysqlcppconn dbDao)
target_link_libraries(netWorkTest netWork)
