cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GLAD C)

add_library(glad SHARED "src/glad.c")

target_compile_definitions(glad PRIVATE GLAD_GLAPI_EXPORT)
target_compile_definitions(glad PRIVATE GLAD_GLAPI_EXPORT_BUILD)

target_include_directories(glad PUBLIC "./include/")

#=== Install Targets
#archive file is not required
install(TARGETS glad 
	RUNTIME DESTINATION "bin"
	LIBRARY DESTINATION "lib"
	ARCHIVE DESTINATION "lib"
	INCLUDES DESTINATION "include")
