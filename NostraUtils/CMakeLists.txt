cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project("NostraUtils" CXX)

# Set language standard
if ("${NOE_CPP14_COMPATIBLILTY_MODE}")
	set (CMAKE_CXX_STANDARD 14)
	message(STATUS "NOU:  Generating for C++14 compatibility mode.")
	add_definitions(-DNOU_CPP14_COMPATIBILITY)
else()
	set (CMAKE_CXX_STANDARD 17)
	message(STATUS "NOU:  Generating without C++14 compatibility mode.")
endif()

if (${COMPILE_AS_DEBUG})
	add_definitions (-DNOU_DEBUG)
endif()
#===

#=== Set name of the NostraUtils include file location
if(NOT DEFINED NOU_INCLUDE_DIR)
	set(NOU_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Nostra Utils/src/header")
endif()
#=== 

#=== Set name of the NostraUtils library file(s)
if(NOT DEFINED NOU_LIB_NAME)
	set(NOU_LIB_NAME "NostraUtils")
endif()
#=== 

#Build NostraUtils library
add_subdirectory("Nostra Utils")

# Installation only from here on
message(STATUS "NOU:  The files will be installed to: ${CMAKE_INSTALL_PREFIX}")
