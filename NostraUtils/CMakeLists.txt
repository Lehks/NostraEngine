cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

# Set language standard
if ("${NOE_CPP14_COMPATIBLILTY_MODE}")
	set (CMAKE_CXX_STANDARD 14)
	message(STATUS "NOU:  Generating for C++14 compatibility mode.")
	add_definitions(-DNOU_CPP14_COMPATIBILITY)
else()
	set (CMAKE_CXX_STANDARD 17)
	message(STATUS "NOU:  Generating without C++14 compatibility mode.")
endif()
#===

#Build NostraUtils library
add_subdirectory("Nostra Utils")