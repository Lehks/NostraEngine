cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project("${NOE_PROJECT_NAME}" 
	VERSION "${NOE_PROJECT_VERSION}"
	DESCRIPTION "${NOE_PROJECT_DESCRIPTION}"
	#HOMEPAGE_URL "${NOE_PROJECT_HOMEPAGE}" 
	LANGUAGES C CXX)

add_subdirectory("doc")

file(GLOB_RECURSE NOE_NOE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/NostraEngine/src/source/nostraengine/*.cpp")

add_library(NostraEngineDbg SHARED ${NOE_NOE_SOURCE_FILES})

target_include_directories(NostraEngineDbg 
	PUBLIC 
		"src/header")

target_link_libraries(NostraEngineDbg 
	PUBLIC 
		Nostra::Utils
	PRIVATE 
		sqlite3)
		
target_compile_definitions(NostraEngineDbg 
	INTERFACE 
		"NOE_DLL")

if(MSVC)
	target_compile_options(NostraEngineDbg
		PRIVATE
			"/wd4251"
			"/WX")
endif()

install(TARGETS NostraEngineDbg DESTINATION "bin" INCLUDES DESTINATION "include")
#[==[	
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")

	include_directories("${NOE_NOE_INCLUDE_DIR}")
	include_directories("${NOE_GLAD_INCLUDE_DIR}")
	include_directories("${NOE_NOU_INCLUDE_DIR}")
	include_directories("${CMAKE_SOURCE_DIR}")
	
	add_library("${NOE_NOE_LIB_NAME}" SHARED "${NOE_NOE_SOURCE_FILES}")
	
	target_link_libraries(${NOE_NOE_LIB_NAME} PRIVATE sqlite3::sqlite3)

	target_link_libraries("${NOE_NOE_LIB_NAME}" "${NOE_GLAD_LIB_NAME}")
	#target_link_libraries("${NOE_NOE_LIB_NAME}" "${NOE_SQLITE3_LIB_NAME}")
	target_link_libraries("${NOE_NOE_LIB_NAME}" "${NOE_NOU_LIB_NAME}")
	
	add_dependencies("${NOE_NOE_LIB_NAME}" "${NOE_GLAD_LIB_NAME}")
	#add_dependencies("${NOE_NOE_LIB_NAME}" "${NOE_SQLITE3_LIB_NAME}")
	add_dependencies("${NOE_NOE_LIB_NAME}" "${NOE_NOU_LIB_NAME}")

	install(TARGETS "${NOE_NOE_LIB_NAME}" DESTINATION "${NOE_BINARY_INSTALL_DIR}")

endif()
#]==]
