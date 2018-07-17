cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GLSLGenerator CXX)

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(GLSLGenerator SHARED "${files}" "GLSLGeneratorPlugin.cpp")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_link_libraries(GLSLGenerator
		PRIVATE 
			NostraEngineDbg)
else()
	target_link_libraries(GLSLGenerator
		PRIVATE 
			NostraEngine)
endif()

target_compile_definitions(GLSLGenerator
	PRIVATE
		NOE_PLUGIN)

target_include_directories(GLSLGenerator
	PRIVATE
		"src")

set_target_properties(GLSLGenerator PROPERTIES PREFIX "")
set_target_properties(GLSLGenerator PROPERTIES SUFFIX ".np")

install(TARGETS GLSLGenerator
	RUNTIME DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}" 
	LIBRARY DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
install(FILES "GLSLGenerator.pconf" DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
