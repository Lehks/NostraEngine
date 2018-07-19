cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GLRenderableImpl CXX)

#===GLAD===

#=== Variables for GLAD 
set(NOE_GLAD_LIB_NAME "GLAD")
set(NOE_GLAD_LIB_CONFIG "SHARED") #Either STATIC or SHARED
#===

add_subdirectory("GLFW")

#==========

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(GLRenderableImpl SHARED "${files}" "GLRenderableImplPlugin.cpp")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_link_libraries(GLRenderableImpl 
		PRIVATE 
			NostraEngineDbg
			GLAD)
else()
	target_link_libraries(GLRenderableImpl 
		PRIVATE 
			NostraEngine
			GLAD)
endif()

target_compile_definitions(GLRenderableImpl 
	PRIVATE
		NOE_PLUGIN
		GLAD_DLL)

target_include_directories(GLRenderableImpl 
	PRIVATE
		"GLAD/include"
		"glad")

set_target_properties(GLRenderableImpl PROPERTIES PREFIX "")
set_target_properties(GLRenderableImpl PROPERTIES SUFFIX ".np")

install(TARGETS GLRenderableImpl
	RUNTIME DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}" 
	LIBRARY DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
install(FILES "GLRenderableImpl.pconf" DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
