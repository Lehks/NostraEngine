cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project("NostraEngine" CXX)

# set C++17 as language standard
set (CMAKE_CXX_STANDARD 17)

#=== set bin/ as output directory
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#===

#=== If COMPILE_AS_DEBUG is True, NOE_DEBUG will be defined during the compilation. 
#COMPILE_AS_DEBUG will be False if in Release mode and True in Debug mode by default.
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	set (NOE_COMPILE_AS_DEBUG False CACHE BOOL "If true, the project will be compiled with the macro NOE_DEBUG.")
else()
	set (NOE_COMPILE_AS_DEBUG True CACHE BOOL "If true, the project will be compiled with the macro NOE_DEBUG.")
endif()

if (${NOE_COMPILE_AS_DEBUG})
	add_definitions (-DNOE_DEBUG)
endif()
#===

#=== Variables for NostraEngine target
set(NOE_EXECUTABLE "NostraEngineExe")
set(NOE_EXECUTABLE_SOURCE "main.cpp")
#===

#=== Variables for Test target
set(NOE_TEST_EXECUTABLE "Test")
set(NOE_TEST_EXECUTABLE_SOURCE "testmain.cpp")
#===

#=== Include directory variables
set(NOE_GLFW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/GLFW/include")
set(NOE_GLAD_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/GLAD/include")
set(NOE_NOU_INCLUDE_DIR  "${PROJECT_SOURCE_DIR}/NostraEngine/src/header")
#===

#=== Variables for GLFW 
set(NOE_GLFW_LIB_NAME "glfw")
set(NOE_GLFW_LIB_CONFIG "SHARED") #Either STATIC or SHARED
#===

#=== Variables for GLAD
set(NOE_GLAD_LIB_NAME "glad")
#===

#=== Variables for SQLite3
set(NOE_SQLITE3_LIB_NAME "sqlite3")
#===

#== Variables for Nostra Engine
set(NOE_NOE_LIB_NAME "NostraEngine")
#==

#Build GLFW
add_subdirectory ("GLFW")

#Build GLAD
add_subdirectory("GLAD")

#Build SQLite3
add_subdirectory("SQLite3")

#Build Nostra Engine
add_subdirectory("NostraEngine")

#Add include directories
include_directories("${NOE_GLFW_INCLUDE_DIR}")
include_directories("${NOE_GLAD_INCLUDE_DIR}")
include_directories("${NOE_NOU_INCLUDE_DIR}")

#=== Build NostraEngine target
add_executable("${NOE_EXECUTABLE}" "${NOE_EXECUTABLE_SOURCE}")

target_link_libraries("${NOE_EXECUTABLE}" "${NOE_GLFW_LIB_NAME}")
target_link_libraries("${NOE_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
target_link_libraries("${NOE_EXECUTABLE}" "${NOE_SQLITE3_LIB_NAME}")
target_link_libraries("${NOE_EXECUTABLE}" "${NOE_NOE_LIB_NAME}")

add_dependencies("${NOE_EXECUTABLE}" "${NOE_GLFW_LIB_NAME}")
add_dependencies("${NOE_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
add_dependencies("${NOE_EXECUTABLE}" "${NOE_SQLITE3_LIB_NAME}")
add_dependencies("${NOE_EXECUTABLE}" "${NOE_NOE_LIB_NAME}")
#===

#=== Build Test target
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	message(STATUS "NOE:  Building in Debug mode, Test-executable will be generated.")

	#Create testmain.cpp if it does not exist
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/${NOE_TEST_EXECUTABLE_SOURCE}")
		message(STATUS "NOE:  ${NOE_TEST_EXECUTABLE_SOURCE} was not found. A default one will be generated.")
		FILE(WRITE "${CMAKE_SOURCE_DIR}/${NOE_TEST_EXECUTABLE_SOURCE}" "\n\nint main()\n{\n\treturn 0;\n}")
	endif()
	


	add_executable("${NOE_TEST_EXECUTABLE}" "${NOE_TEST_EXECUTABLE_SOURCE}")

	target_link_libraries("${NOE_TEST_EXECUTABLE}" "${NOE_GLFW_LIB_NAME}")
	target_link_libraries("${NOE_TEST_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
	target_link_libraries("${NOE_TEST_EXECUTABLE}" "${NOE_SQLITE3_LIB_NAME}")
	target_link_libraries("${NOE_TEST_EXECUTABLE}" "${NOE_NOE_LIB_NAME}")

	add_dependencies("${NOE_TEST_EXECUTABLE}" "${NOE_GLFW_LIB_NAME}")
	add_dependencies("${NOE_TEST_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
	add_dependencies("${NOE_TEST_EXECUTABLE}" "${NOE_SQLITE3_LIB_NAME}")
	add_dependencies("${NOE_TEST_EXECUTABLE}" "${NOE_NOE_LIB_NAME}")
else()
	message(STATUS "NOE:  Building in Release mode, Test-executable will not be generated.")
endif()
#=== 