cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GLRenderable CXX)

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(GLRenderable SHARED "${files}" "GLRenderablePlugin.cpp")

target_link_libraries(GLRenderable 
	PRIVATE 
		Nostra::Engine
		glad)

target_compile_definitions(GLRenderable 
	PRIVATE
		NOE_PLUGIN)

target_include_directories(GLRenderable 
	PRIVATE
		"src")

set_target_properties(GLRenderable PROPERTIES PREFIX "")
set_target_properties(GLRenderable PROPERTIES SUFFIX ".np")

install(TARGETS GLRenderable
	RUNTIME DESTINATION "bin/plugins" 
	LIBRARY DESTINATION "bin/plugins")
install(FILES "GLRenderable.pconf" DESTINATION "bin/plugins")
