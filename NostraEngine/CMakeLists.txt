cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

file(GLOB source_files "src/source/nostraengine/*/*.c*")

include_directories("${PROJECT_SOURCE_DIR}/NostraEngine/src/header")
include_directories("${PROJECT_SOURCE_DIR}/NostraEngine/dependencies/include")

add_library(NostraEngine_STATIC STATIC "${source_files}")
#add_library(NostraEngine_SHARED SHARED "${source_files}")

set_target_properties(NostraEngine_STATIC PROPERTIES LINKER_LANGUAGE CXX)
#set_target_properties(NostraEngine_SHARED PROPERTIES LINKER_LANGUAGE CXX)

link_directories("NostraEngine/dependencies/lib/GLFW/x86/")
#link_directories("NostraEngine/dependencies/lib/nostrautils/Release/x86/")

target_link_libraries(NostraEngine_STATIC NostraUtils_STATIC.lib)
target_link_libraries(NostraEngine_STATIC glfw3.lib)
#target_link_libraries(NostraEngine_SHARED NostraUtils_STATIC.lib)
#target_link_libraries(NostraEngine_SHARED glfw3.lib)