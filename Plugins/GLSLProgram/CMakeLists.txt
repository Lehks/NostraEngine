cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GLSLProgram CXX)

#==========

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(GLSLProgram SHARED "${files}" "GLSLProgramPlugin.cpp")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_link_libraries(GLSLProgram
		PRIVATE
			NostraEngineDbg
			)
else()
	target_link_libraries(GLSLProgram
		PRIVATE
			NostraEngine
			)
endif()

target_compile_definitions(GLSLProgram
	PRIVATE
		NOE_PLUGIN
		)

target_include_directories(GLSLProgram
	PRIVATE
		"src")

set_target_properties(GLSLProgram PROPERTIES PREFIX "")
set_target_properties(GLSLProgram PROPERTIES SUFFIX ".np")

get_target_property(PROP_INCLUDE GLSLProgram INCLUDE_DIRECTORIES)

message(STATUS ${PROP_INCLUDE})

install(TARGETS GLSLProgram
	RUNTIME DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}"
	LIBRARY DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
install(FILES "GLSLProgram.pconf" DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
