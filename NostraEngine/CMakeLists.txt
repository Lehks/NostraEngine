cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project("${NOE_PROJECT_NAME}" 
	VERSION "${NOE_PROJECT_VERSION}"
	DESCRIPTION "${NOE_PROJECT_DESCRIPTION}"
	#HOMEPAGE_URL "${NOE_PROJECT_HOMEPAGE}" 
	LANGUAGES C CXX)

add_subdirectory("doc")

file(GLOB_RECURSE NOE_NOE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/NostraEngine/src/source/nostraengine/*.cpp")

add_library(NostraEngineDbg SHARED ${NOE_NOE_SOURCE_FILES})
add_library(Nostra::EngineDbg ALIAS NostraEngineDbg)

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
else()
	target_compile_options(NostraEngineDbg
		PRIVATE
			"-Werror")
endif()

install(TARGETS NostraEngineDbg 
	RUNTIME DESTINATION "bin"
	LIBRARY DESTINATION "lib"
	ARCHIVE DESTINATION "lib"
	INCLUDES DESTINATION "include")

install(DIRECTORY "src/header/" DESTINATION "include")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")

	add_library(NostraEngine SHARED ${NOE_NOE_SOURCE_FILES})
	add_library(Nostra::EngineDbg ALIAS NostraEngine)

	target_include_directories(NostraEngine 
		PUBLIC 
			"src/header")

	target_link_libraries(NostraEngine 
		PUBLIC 
			Nostra::Utils
		PRIVATE 
			sqlite3)

	target_compile_definitions(NostraEngine 
		INTERFACE 
			"NOE_DLL")

	if(MSVC)
		target_compile_options(NostraEngine
			PRIVATE
				"/wd4251"
				"/WX")
	else()
		target_compile_options(NostraEngine
			PRIVATE
				"-Werror")
	endif()

	install(TARGETS NostraEngine 
		RUNTIME DESTINATION "bin"
		LIBRARY DESTINATION "lib"
		ARCHIVE DESTINATION "lib"
		INCLUDES DESTINATION "include")

endif()
