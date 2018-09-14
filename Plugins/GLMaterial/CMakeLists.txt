cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(GLMaterial CXX)

#==========

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(GLMaterial SHARED "${files}" "GLMaterialPlugin.cpp")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_link_libraries(GLMaterial
		PRIVATE
			NostraEngineDbg
			)
else()
	target_link_libraries(GLMaterial
		PRIVATE
			NostraEngine
			)
endif()

target_compile_definitions(GLMaterial
	PRIVATE
		NOE_PLUGIN
		)

target_include_directories(GLMaterial
	PRIVATE
		"src")

set_target_properties(GLMaterial PROPERTIES PREFIX "")
set_target_properties(GLMaterial PROPERTIES SUFFIX ".np")

get_target_property(PROP_INCLUDE GLMaterial INCLUDE_DIRECTORIES)

message(STATUS ${PROP_INCLUDE})

install(TARGETS GLMaterial
	RUNTIME DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}"
	LIBRARY DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
install(FILES "GLMaterial.pconf" DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
