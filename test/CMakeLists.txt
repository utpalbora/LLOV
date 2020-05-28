set(LLVM_SHLIBEXT "${CMAKE_SHARED_MODULE_SUFFIX}")

add_custom_target(check-llov)
set_target_properties(check-llov PROPERTIES FOLDER "OpenMPVerify")

if(NOT LLVM_MAIN_SRC_DIR)
  find_program(LLVM_OPT NAMES opt HINTS ${LLVM_TOOLS_BINARY_DIR})
  find_program(LLVM_CLANG NAMES clang HINTS ${LLVM_TOOLS_BINARY_DIR})
  find_program(LLVM_FILECHECK NAMES FileCheck HINTS ${LLVM_TOOLS_BINARY_DIR})
  find_program(LLVM_NOT NAMES not HINTS ${LLVM_TOOLS_BINARY_DIR})
  if (NOT LLVM_OPT)
    message(WARNING "LLVM's opt program could not be found. Please set LLVM_OPT.")
  endif()
  if (NOT LLVM_FILECHECK)
    message(WARNING "LLVM's FileCheck program could not be found. "
      "Please set LLVM_FILECHECK. Please set LLVM_FILECHECK.")
  endif()
  if (NOT LLVM_NOT)
    message(WARNING "LLVM's not program could not be found. Please set LLVM_NOT.")
  endif()
  set(LLOV_TEST_DEPS OpenMPVerify)
else ()
  set(LLVM_OPT "${LLVM_TOOLS_BINARY_DIR}/opt")
  set(LLVM_CLANG "${LLVM_TOOLS_BINARY_DIR}/clang")
  set(LLVM_FILECHECK "${LLVM_TOOLS_BINARY_DIR}/FileCheck")
  set(LLVM_NOT "${LLVM_TOOLS_BINARY_DIR}/not")
  set(LLOV_TEST_DEPS llvm-config clang opt LLVMPolly OpenMPVerify FileCheck not)
endif()

set(LLVM_BINARY_DIR "${LLVM_BINARY_DIR}")
set(LLVM_TOOLS_DIR "${LLVM_TOOLS_BINARY_DIR}")
set(LLVM_LIBS_DIR "${LLVM_BINARY_DIR}/lib${LLVM_LIBDIR_SUFFIX}")
if (CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(LLOV_LIB_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
else()
  set(LLOV_LIB_DIR "${LLVM_BINARY_DIR}/lib")
endif()

configure_lit_site_cfg(
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.in
  ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg)

# Run regression tests
add_lit_testsuite(check-llov-tests "Running LLOV regression tests"
  ${CMAKE_CURRENT_BINARY_DIR}
  PARAMS llov_site_config=${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg
  DEPENDS ${LLOV_TEST_DEPS}
  )
add_dependencies(check-llov check-llov-tests)

# Run llov-check-format as part of check-llov only if we are compiling with
# clang, so clang-format is available.
# if (TARGET clang-format) would be preferable, but this target is only added
# after Polly, i.e. there is no such target yet at this point. The CMake cache
# entry LLVM_TOOL_CLANG_BUILD will only be defined after clang has been
# configured at least once, i.e. format will be checked only after a rerun of
# CMake's configure.
if (LLVM_TOOL_CLANG_BUILD)
  add_dependencies(check-llov llov-check-format)
endif ()
