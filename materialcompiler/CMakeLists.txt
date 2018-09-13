cmake_minimum_required(VERSION 3.8.2)

option(GENERATE_FLEX_BISON "Whether CMake should generate Flex/Bison Header/Source files." ON)

if(GENERATE_FLEX_BISON)
    find_package(FLEX)

    if(NOT FLEX_FOUND)
        message(SEND_ERROR "Flex not found")
    endif()

    flex_target(NostraEngineTokenizer Tokenizer.l  ${CMAKE_CURRENT_BINARY_DIR}/MaterialTokenizer.c)

    find_package(BISON)

    if(NOT BISON_FOUND)
        message(SEND_ERROR "Bison not found")
    endif()

    bison_target(NostraEngineParser Parser.y ${CMAKE_CURRENT_BINARY_DIR}/MaterialParser.c)
    
    add_flex_bison_dependency(NostraEngineTokenizer NostraEngineParser)

    add_library(NostraEngineCompiler STATIC 
        ${FLEX_NostraEngineTokenizer_OUTPUTS}
        ${BISON_NostraEngineParser_OUTPUT_SOURCE}
    )

	target_include_directories(NostraEngineCompiler
		PUBLIC
			"${CMAKE_CURRENT_BINARY_DIR}")
endif()