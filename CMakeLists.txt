cmake_minimum_required(VERSION 3.16)
project(Quack)
set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

find_package(BISON 3.7.1 REQUIRED)
find_package(FLEX 2.6.4 REQUIRED)
find_package(LLVM 10.0.0 REQUIRED)

message(STATUS "LLVM DIR: ${LLVM_DIR}")
message(STATUS "LLVM INCLUDE DIR: ${LLVM_INCLUDE_DIRS}")
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

add_definitions(${LLVM_DEFINITIONS})

BISON_TARGET(Parser src/Parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp VERBOSE )
FLEX_TARGET(Lexer src/Lexer.lpp  ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

include_directories(${LLVM_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} include)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader target native executionengine mcjit linker passes)
set(LLVM_LINK_COMPONENTS
        LLVMAnalysis
        LLVMCore
        LLVMExecutionEngine
        LLVMInstCombine
        LLVMObject
        LLVMOrcJIT
        LLVMRuntimeDyld
        LLVMScalarOpts
        LLVMSupport
        )

add_executable(
        quack
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Lexer_OUTPUTS}
        src/AST.cpp
        src/Builtin.cpp
        src/Environment.cpp
        src/EnvironmentBuilder.cpp
        src/ExprTypeChecker.cpp
        src/FnCodeGen.cpp
        src/LLVMType.cpp
        src/main.cpp
        src/ParserDriver.cpp
        src/PrintVisitor.cpp
        src/QType.cpp
        src/QTypeDB.cpp
        src/StmtTypeChecker.cpp
        src/TypeChecker.cpp
        src/Utils.cpp)

target_link_libraries(quack ${llvm_libs} ${LLVM_LINK_COMPONENTS})
