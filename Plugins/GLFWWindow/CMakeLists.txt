cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GLFWWindow CXX)

#===GLFW===

#=== Variables for GLFW 
set(NOE_GLFW_LIB_NAME "glfw")
set(NOE_GLFW_LIB_CONFIG "SHARED") #Either STATIC or SHARED
#===

add_subdirectory("GLFW")

#==========

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(GLFWWindow SHARED "${files}" "GLFWWindowPlugin.cpp")

target_link_libraries(GLFWWindow 
		PRIVATE 
			Nostra::Engine
			glfw)

target_compile_definitions(GLFWWindow 
	PRIVATE
		NOE_PLUGIN
		GLFW_DLL)

target_include_directories(GLFWWindow 
	PRIVATE
		"GLFW/include"
		"src")

set_target_properties(GLFWWindow PROPERTIES PREFIX "")
set_target_properties(GLFWWindow PROPERTIES SUFFIX ".np")

install(TARGETS GLFWWindow
	RUNTIME DESTINATION "bin/plugins" 
	LIBRARY DESTINATION "bin/plugins")
install(FILES "GLFWWindow.pconf" DESTINATION "bin/plugins")
