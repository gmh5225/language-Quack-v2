configure_file(lit.site.cfg.py.in
               lit.site.cfg.py @ONLY)

if (EXISTS ${LLVM_TOOLS_BINARY_DIR}/llvm-lit)
    set(LLVM_LIT_BIN ${LLVM_TOOLS_BINARY_DIR}/llvm-lit)
else()
    message(STATUS "llvm-lit wasn't found in ${LLVM_TOOLS_BINARY_DIR}")
    find_program(LLVM_LIT_BIN lit)
    if (NOT LLVM_LIT_BIN)
        find_program(LLVM_LIT_ALT llvm-lit)
        if (NOT LLVM_LIT_ALT)
            message(FATAL_ERROR "llvm-lit wasn't found. It is needed for testing.")
        endif()
        set(LLVM_LIT_BIN LLVM_LIT_ALT)
    endif()
    message(STATUS "llvm-lit: using ${LLVM_LIT_BIN}")
endif()

add_custom_target(check
        COMMAND ${LLVM_LIT_BIN} "${CMAKE_CURRENT_BINARY_DIR}" -v
        DEPENDS
        quick)