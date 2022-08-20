cmake_minimum_required(VERSION 3.16)
project(Quick)
set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

find_package(BISON 3.7.1 REQUIRED)
find_package(FLEX 2.6.4 REQUIRED)
find_package(LLVM CONFIG REQUIRED)

message(STATUS "LLVM DIR: ${LLVM_DIR}")
message(STATUS "LLVM INCLUDE DIR: ${LLVM_INCLUDE_DIRS}")
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

include_directories(${LLVM_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
        include
        ${CMAKE_CURRENT_BINARY_DIR}/src)

add_subdirectory(src)
add_subdirectory(test)