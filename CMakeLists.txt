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

#=== Variables for NostraEngine target
set(NOE_EXECUTABLE "NostraEngine")
set(NOE_EXECUTABLE_SOURCE "main.cpp")
#===

#=== Variables for Test target
set(NOE_TEST_EXECUTABLE "Test")
set(NOE_TEST_EXECUTABLE_SOURCE "testmain.cpp")
#===

#=== Include directory variables
set(NOE_GLFW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/GLFW/include")
set(NOE_GLAD_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/GLAD/include")
#===

#=== Vaiables for GLFW 
set(NOE_GLFW_LIB_NAME "glfw")
set(NOE_GLFW_LIB_CONFIG "SHARED") #Either STATIC or SHARED
#===

#=== Variables for GLAD
set(NOE_GLAD_LIB_NAME "glad")
#===

#Build GLFW
add_subdirectory ("GLFW")

#Build GLAD
add_subdirectory("GLAD")

#Add include directories
include_directories("${NOE_GLFW_INCLUDE_DIR}")
include_directories("${NOE_GLAD_INCLUDE_DIR}")

#=== Build NostraEngine target
add_executable("${NOE_EXECUTABLE}" "${NOE_EXECUTABLE_SOURCE}")
target_link_libraries("${NOE_EXECUTABLE}" "${NOE_GLFW_LIB_NAME}")
target_link_libraries("${NOE_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
add_dependencies("${NOE_EXECUTABLE}" "${NOE_GLFW_LIB_NAME}")
add_dependencies("${NOE_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
#===


#=== Build Test target
add_executable("${NOE_TEST_EXECUTABLE}" "${NOE_TEST_EXECUTABLE_SOURCE}")
target_link_libraries("${NOE_TEST_EXECUTABLE}" "${NOE_GLFW_LIB_NAME}")
target_link_libraries("${NOE_TEST_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
add_dependencies("${NOE_EXECUTABLE}" "${NOE_GLFW_LIB_NAME}")
add_dependencies("${NOE_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
#=== 