cmake_minimum_required(VERSION 3.0)

set (CMAKE_C_COMPILER   "/opt/gcc-4.1.2/bin/gcc")
set (CMAKE_CXX_COMPILER "/opt/gcc-4.1.2/bin/g++")
### for crti.o not found
SET(ENV{LIBRARY_PATH} "/usr/lib/x86_64-linux-gnu/:$LIBRARY_PATH")

#set (CMAKE_C_COMPILER   "/usr/bin/gcc")
#set (CMAKE_CXX_COMPILER "/usr/bin/g++")

project(boost_test)

include_directories(${CMAKE_SOURCE_DIR}/boost)
include_directories(${CMAKE_SOURCE_DIR}/src)

link_directories(${CMAKE_SOURCE_DIR}/boost/lib64)

# to check preprocessor files
#add_compile_options (-save-temp) 

include(CTest)
enable_testing()


add_subdirectory(src)
add_subdirectory(test)
