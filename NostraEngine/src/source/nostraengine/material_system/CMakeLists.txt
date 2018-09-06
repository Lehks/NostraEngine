CMAKE_MINIMUM_REQUIRED(VERSION 3.8.2)

set(GENERATE_FLEX_BISON FALSE CACHE BOOL "Wether CMake should generate Flex/Bison Header/Source files.")

if(GENERATE_FLEX_BISON)
    find_package(FLEX)
    if(NOT FLEX_FOUND)
        message(SEND_ERROR "Flex not found")
    endif()
    FLEX_TARGET(MATERIAL_TOKENIZER Tokenizer.l  ${CMAKE_CURRENT_BINARY_DIR}/MaterialTokenizer.cpp)

    find_package(BISON)
    if(NOT BISON_FOUND)
        message(SEND_ERROR "Bison not found")
    endif()
    BISON_TARGET(MATERIAL_PARSER Parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/MaterialParser.cpp)
    
    
    ADD_FLEX_BISON_DEPENDENCY(MATERIAL_TOKENIZER MATERIAL_PARSER)

    add_library(compilerfrontend STATIC 
        ${FLEX_MATERIAL_TOKENIZER_OUTPUTS}
        ${BISON_MATERIAL_PARSER_OUTPUTS}
    )

    target_include_directories(compilerfrontend
        PUBLIC
            "${PROJECT_SOURCE_DIR}/src/header"
    )

endif()