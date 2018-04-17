cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(GLAD C)

include_directories("${NOE_GLAD_INCLUDE_DIR}")

add_definitions(-DGLAD_GLAPI_EXPORT)
add_definitions(-DGLAD_GLAPI_EXPORT_BUILD)

add_library("${NOE_GLAD_LIB_NAME}" SHARED "src/glad.c")

install(TARGETS "${NOE_GLAD_LIB_NAME}" DESTINATION "bin")