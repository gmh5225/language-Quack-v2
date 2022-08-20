add_definitions(${LLVM_DEFINITIONS})

BISON_TARGET(Parser Parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp VERBOSE )
FLEX_TARGET(Lexer Lexer.lpp  ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

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
        quick
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Lexer_OUTPUTS}
        AST.cpp
        Builtin.cpp
        Environment.cpp
        EnvironmentBuilder.cpp
        ExprTypeChecker.cpp
        FnCodeGen.cpp
        LLVMType.cpp
        main.cpp
        ParserDriver.cpp
        PrintVisitor.cpp
        QType.cpp
        QTypeDB.cpp
        StmtTypeChecker.cpp
        TypeChecker.cpp
        Utils.cpp)

set_target_properties(quick PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
target_link_libraries(quick ${llvm_libs} ${LLVM_LINK_COMPONENTS})