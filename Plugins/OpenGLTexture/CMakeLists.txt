cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(OpenGLTexture CXX)

#==========

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(OpenGLTexture SHARED "${files}" "OpenGLTexturePlugin.cpp")

target_link_libraries(OpenGLTexture
		PRIVATE
			Nostra::Engine
			glad)

target_compile_definitions(OpenGLTexture
	PRIVATE
		NOE_PLUGIN
		)

target_include_directories(OpenGLTexture
	PRIVATE
		"src"
		)

set_target_properties(OpenGLTexture PROPERTIES PREFIX "")
set_target_properties(OpenGLTexture PROPERTIES SUFFIX ".np")

install(TARGETS OpenGLTexture
	RUNTIME DESTINATION "bin/plugins"
	LIBRARY DESTINATION "bin/plugins")
install(FILES "OpenGLTexture.pconf" DESTINATION "bin/plugins")
