cmake_minimum_required(VERSION 3.16)
project(Quick)
set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

find_package(BISON 3.7.1 REQUIRED)
find_package(FLEX 2.6.4 REQUIRED)
find_package(LLVM CONFIG REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
        include
        ${CMAKE_CURRENT_BINARY_DIR}/src)
add_definitions(${LLVM_DEFINITIONS})
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

add_subdirectory(src)
add_subdirectory(test)