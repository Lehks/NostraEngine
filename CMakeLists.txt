cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

project("NostraEngine" CXX)

option(NOE_CPP14_COMPATIBLILTY_MODE "Disables some C++17-only features." OFF)

# Set language standard
if ("${NOE_CPP14_COMPATIBLILTY_MODE}")
	set (CMAKE_CXX_STANDARD 14)
	message(STATUS "NOE:  Generating for C++14 compatibility mode.")
	add_definitions(-DNOU_CPP14_COMPATIBILITY)
else()
	set (CMAKE_CXX_STANDARD 17)
	message(STATUS "NOE:  Generating without C++14 compatibility mode.")
endif()

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

#=== Set RPATH
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/bin")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#===

#=== Set stdlib++ for AppleClang
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
	add_definitions("-stdlib=libc++ -lc++experimental")
	
endif()
#===

#=== Variables for NostraEngine target
set(NOE_EXECUTABLE "NostraEngineExe")
set(NOE_EXECUTABLE_SOURCE "main.cpp")
#===

#=== Variables for Test target
set(NOE_TEST_EXECUTABLE "Test")
set(NOE_TEST_EXECUTABLE_SOURCE "testmain.cpp")
set(NOE_TEST_EXECUTABLE_SOURCE_TEMPLATE "testmain.cpp.in")
#===

#=== Include directory variables
set(NOE_GLAD_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/GLAD/include")
set(NOE_NOE_INCLUDE_DIR  "${PROJECT_SOURCE_DIR}/NostraEngine/src/header")
set(NOE_NOU_INCLUDE_DIR  "${PROJECT_SOURCE_DIR}/NostraUtils/Nostra Utils/src/header")
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

#== Variables for Nostra Utils
set(NOE_NOU_LIB_NAME "NostraUtils")
#==

#Build GLAD
add_subdirectory("GLAD")

#Build SQLite3
add_subdirectory("SQLite3")

#Build Nostra Engine
add_subdirectory("NostraEngine")

#Build Nostra Utils
add_subdirectory("NostraUtils")

#Build Plugins
add_subdirectory("Plugins")

#Add include directories
include_directories("${NOE_GLAD_INCLUDE_DIR}")
include_directories("${NOE_NOE_INCLUDE_DIR}")
include_directories("${NOE_NOU_INCLUDE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}")

#=== Build NostraEngine target
add_executable("${NOE_EXECUTABLE}" "${NOE_EXECUTABLE_SOURCE}")

target_link_libraries("${NOE_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
target_link_libraries("${NOE_EXECUTABLE}" "${NOE_SQLITE3_LIB_NAME}")
target_link_libraries("${NOE_EXECUTABLE}" "${NOE_NOE_LIB_NAME}")
target_link_libraries("${NOE_EXECUTABLE}" "${NOE_NOU_LIB_NAME}")

add_dependencies("${NOE_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
add_dependencies("${NOE_EXECUTABLE}" "${NOE_SQLITE3_LIB_NAME}")
add_dependencies("${NOE_EXECUTABLE}" "${NOE_NOE_LIB_NAME}")
add_dependencies("${NOE_EXECUTABLE}" "${NOE_NOU_LIB_NAME}")

install(TARGETS ${NOE_EXECUTABLE} DESTINATION "bin")
#===

#=== Build Test target
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	message(STATUS "NOE:  Building in Debug mode, Test-executable will be generated.")

	#Create testmain.cpp if it does not exist
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/${NOE_TEST_EXECUTABLE_SOURCE}")
		message(STATUS "NOE:  ${NOE_TEST_EXECUTABLE_SOURCE} was not found. A default one will be generated.")
		configure_file("${CMAKE_SOURCE_DIR}/${NOE_TEST_EXECUTABLE_SOURCE_TEMPLATE}" 
								"${CMAKE_SOURCE_DIR}/${NOE_TEST_EXECUTABLE_SOURCE}")
	endif()


	add_executable("${NOE_TEST_EXECUTABLE}" "${NOE_TEST_EXECUTABLE_SOURCE}")
	
	target_link_libraries("${NOE_TEST_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
	target_link_libraries("${NOE_TEST_EXECUTABLE}" "${NOE_SQLITE3_LIB_NAME}")
	target_link_libraries("${NOE_TEST_EXECUTABLE}" "${NOE_NOE_LIB_NAME}")
	target_link_libraries("${NOE_TEST_EXECUTABLE}" "${NOE_NOU_LIB_NAME}")
	
	add_dependencies("${NOE_TEST_EXECUTABLE}" "${NOE_GLAD_LIB_NAME}")
	add_dependencies("${NOE_TEST_EXECUTABLE}" "${NOE_SQLITE3_LIB_NAME}")
	add_dependencies("${NOE_TEST_EXECUTABLE}" "${NOE_NOE_LIB_NAME}")
	add_dependencies("${NOE_TEST_EXECUTABLE}" "${NOE_NOU_LIB_NAME}")
	
	install(TARGETS ${NOE_TEST_EXECUTABLE} DESTINATION "bin")
else()
	message(STATUS "NOE:  Building in Release mode, Test-executable will not be generated.")
endif()
#=== 
