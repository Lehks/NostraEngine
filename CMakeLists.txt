cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project("NostraEngine" CXX)

# set C++17 as language standard
set (CMAKE_CXX_STANDARD 17)

#=== set bin/ as output directory
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#===

#=== If COMPILE_AS_DEBUG is True, NOU_DEBUG will be defined during the compilation
set (NOE_COMPILE_AS_DEBUG False CACHE BOOL "If true, the project will be compiled with the macro NOU_DEBUG.")

if (${NOE_COMPILE_AS_DEBUG})
	add_definitions (-DNOE_DEBUG)
endif()
#===

set (NOE_GCC_IDENTIFICATION_MACRO_REM "-U__GNUC__")
set (NOE_MSVC_IDENTIFICATION_MACRO_REM "-U_MSC_VER")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	add_definitions(${NOE_GCC_IDENTIFICATION_MACRO_REM})
	add_definitions(${NOE_MSVC_IDENTIFICATION_MACRO_REM})
endif()

set(NOE_EXECUTABLE "NostraEngine")
set(NOE_EXECUTABLE_SOURCE "main.cpp")

set(NOE_TEST_EXECUTABLE "Test")
set(NOE_TEST_EXECUTABLE_SOURCE "testmain.cpp")

add_executable("${NOE_EXECUTABLE}" "${NOE_EXECUTABLE_SOURCE}")


add_executable("${NOE_TEST_EXECUTABLE}" "${NOE_TEST_EXECUTABLE_SOURCE}")
