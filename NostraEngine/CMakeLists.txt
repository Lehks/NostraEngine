cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

project("NostraEngine" 
	VERSION "0.0.1"
	DESCRIPTION "A real-time game engine."
	#HOMEPAGE_URL "https://www.github.com/Lehks/NostraEngine" 
	LANGUAGES C CXX)

add_subdirectory("doc")

configure_file("${CMAKE_SOURCE_DIR}/cmake/Config.hpp.in" "src/header/nostraengine/core/Config.hpp" @ONLY)

file(GLOB_RECURSE NOE_NOE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/NostraEngine/src/source/nostraengine/*.cpp")

add_library(NostraEngine SHARED ${NOE_NOE_SOURCE_FILES})
add_library(Nostra::Engine ALIAS NostraEngine)

target_include_directories(NostraEngine 
	PUBLIC 
		"src/header"
		"${CMAKE_CURRENT_BINARY_DIR}/src/header")

if(GENERATE_FLEX_BISON)
	target_link_libraries(NostraEngine
		PRIVATE
		NostraEngineCompiler)
endif()

target_link_libraries(NostraEngine 
	PUBLIC 
		Nostra::Utils
	PRIVATE 
		sqlite3
		${CMAKE_DL_LIBS})

target_compile_definitions(NostraEngine 
	INTERFACE 
		NOE_DLL)

target_compile_features(NostraEngine
	PUBLIC 
		cxx_std_17)

if(MSVC)
	target_compile_options(NostraEngine
		PRIVATE
			"/wd4251"
			"/wd4005"
			"/wd4065"
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

install(DIRECTORY "src/header/" DESTINATION "include")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/src/header/nostraengine/core/Config.hpp" 
	DESTINATION "include/nostraengine/core")
