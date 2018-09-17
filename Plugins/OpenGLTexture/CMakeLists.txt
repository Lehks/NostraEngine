cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(OpenGLTexture CXX)

#==========

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(OpenGLTexture SHARED "${files}" "OpenGLTexturePlugin.cpp")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_link_libraries(OpenGLTexture
		PRIVATE
			NostraEngineDbg
			)
else()
	target_link_libraries(OpenGLTexture
		PRIVATE
			NostraEngine
			glad
			)
endif()

target_compile_definitions(OpenGLTexture
	PRIVATE
		NOE_PLUGIN
		)

target_include_directories(OpenGLTexture
	PRIVATE
		"src")

set_target_properties(OpenGLTexture PROPERTIES PREFIX "")
set_target_properties(OpenGLTexture PROPERTIES SUFFIX ".np")

get_target_property(PROP_INCLUDE OpenGLTexture INCLUDE_DIRECTORIES)

message(STATUS ${PROP_INCLUDE})

install(TARGETS OpenGLTexture
	RUNTIME DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}"
	LIBRARY DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
install(FILES "OpenGLTexture.pconf" DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
