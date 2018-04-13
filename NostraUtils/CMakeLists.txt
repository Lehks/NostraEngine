cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(NostraUtils CXX)

file(GLOB_RECURSE NOE_NOU_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/source/nostrautils/*.cpp")

include_directories("${NOE_NOU_INCLUDE_DIR}")

add_library("${NOE_NOU_LIB_NAME}" SHARED "${NOE_NOU_SOURCE_FILES}")