cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(NostraEngine CXX)

file(GLOB_RECURSE NOE_NOE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/NostraEngine/src/source/nostraengine/*.cpp")

include_directories("${NOE_NOE_INCLUDE_DIR}")
include_directories("${NOE_GLFW_INCLUDE_DIR}")
include_directories("${NOE_GLAD_INCLUDE_DIR}")
include_directories("${NOE_NOU_INCLUDE_DIR}")

add_library("${NOE_NOE_LIB_NAME}" SHARED "${NOE_NOE_SOURCE_FILES}")

target_link_libraries("${NOE_NOE_LIB_NAME}" "${NOE_GLFW_LIB_NAME}")
target_link_libraries("${NOE_NOE_LIB_NAME}" "${NOE_GLAD_LIB_NAME}")
target_link_libraries("${NOE_NOE_LIB_NAME}" "${NOE_SQLITE3_LIB_NAME}")
target_link_libraries("${NOE_NOE_LIB_NAME}" "${NOE_NOU_LIB_NAME}")

add_dependencies("${NOE_NOE_LIB_NAME}" "${NOE_GLFW_LIB_NAME}")
add_dependencies("${NOE_NOE_LIB_NAME}" "${NOE_GLAD_LIB_NAME}")
add_dependencies("${NOE_NOE_LIB_NAME}" "${NOE_SQLITE3_LIB_NAME}")
add_dependencies("${NOE_NOE_LIB_NAME}" "${NOE_NOU_LIB_NAME}")

install(TARGETS "${NOE_NOE_LIB_NAME}" DESTINATION "bin")