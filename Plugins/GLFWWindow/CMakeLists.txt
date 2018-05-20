cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

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

set(TARGET_NAME GLFWWindow)

file(GLOB_RECURSE "files" "src/*.cpp")

include_directories("${NOE_NOE_INCLUDE_DIR}")
include_directories("${NOE_GLAD_INCLUDE_DIR}")
include_directories("${NOE_NOU_INCLUDE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}")

add_library(${TARGET_NAME} SHARED "${files}")

target_link_libraries("${TARGET_NAME}" "${NOE_GLFW_LIB_NAME}")
target_link_libraries("${TARGET_NAME}" "${NOE_GLAD_LIB_NAME}")
target_link_libraries("${TARGET_NAME}" "${NOE_NOU_LIB_NAME}")

add_dependencies("${TARGET_NAME}" "${NOE_GLFW_LIB_NAME}")
add_dependencies("${TARGET_NAME}" "${NOE_GLAD_LIB_NAME}")
add_dependencies("${TARGET_NAME}" "${NOE_NOU_LIB_NAME}")

set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")
set_target_properties(${TARGET_NAME} PROPERTIES SUFFIX ".np")

install(TARGETS ${TARGET_NAME} DESTINATION "bin/plugins")
install(FILES "${TARGET_NAME}.pconf" DESTINATION "bin/plugins")


if(WIN32)
    file(REMOVE "${CMAKE_INSTALL_PREFIX}/${TARGET_NAME}.lib")
endif()



