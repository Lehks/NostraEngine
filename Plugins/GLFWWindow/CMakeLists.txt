cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GLFWWindow CXX)

# Set language standard
if ("${NOE_CPP14_COMPATIBLILTY_MODE}")
	set (CMAKE_CXX_STANDARD 14)
	add_definitions(-DNOU_CPP14_COMPATIBILITY)
else()
	set (CMAKE_CXX_STANDARD 17)
endif()

#===GLFW===

#=== Variables for GLFW 
set(NOE_GLFW_LIB_NAME "glfw")
set(NOE_GLFW_LIB_CONFIG "SHARED") #Either STATIC or SHARED
#===

add_subdirectory("GLFW")

#==========

#=== Add flags for debugging
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	add_definitions (-DNOU_DEBUG)
endif()
#===

set(TARGET_NAME GLFWWindow)

file(GLOB_RECURSE "files" "src/*.cpp")

add_library("${TARGET_NAME}" SHARED "${files}" "GLFWWindowPlugin.cpp")

target_link_libraries("${TARGET_NAME}" PRIVATE "${NOE_GLFW_LIB_NAME}")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_link_libraries("${TARGET_NAME}" PRIVATE "${NOE_NOU_DBG_LIB_NAME}")
	target_link_libraries("${TARGET_NAME}" PRIVATE NostraEngineDebug)
else()
	target_link_libraries("${TARGET_NAME}" PRIVATE "${NOE_NOU_LIB_NAME}")
	target_link_libraries("${TARGET_NAME}" PRIVATE NostraEngine)
endif()

set_target_properties("${TARGET_NAME}" PROPERTIES PREFIX "")
set_target_properties("${TARGET_NAME}" PROPERTIES SUFFIX ".np")

install(TARGETS "${TARGET_NAME}" 
	RUNTIME DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}" 
	LIBRARY DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
install(FILES "${TARGET_NAME}.pconf" DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")



