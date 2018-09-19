cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GLSLProgram CXX)

#==========

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(GLSLProgram SHARED "${files}" "GLSLProgramPlugin.cpp")

target_link_libraries(GLSLProgram
		PRIVATE
			Nostra::Engine
			glad)

target_compile_definitions(GLSLProgram
	PRIVATE
		NOE_PLUGIN
		)

target_include_directories(GLSLProgram
	PRIVATE
		"src"
		)

set_target_properties(GLSLProgram PROPERTIES PREFIX "")
set_target_properties(GLSLProgram PROPERTIES SUFFIX ".np")

install(TARGETS GLSLProgram
	RUNTIME DESTINATION "bin/plugins"
	LIBRARY DESTINATION "bin/plugins")
install(FILES "GLSLProgram.pconf" DESTINATION "bin/plugins")
