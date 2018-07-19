cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

project(IniConfiguration CXX)

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(IniConfiguration SHARED "${files}" "IniConfigurationPlugin.cpp")

target_link_libraries(IniConfiguration 
    PRIVATE 
        Nostra::Engine)

target_compile_definitions(IniConfiguration 
    PRIVATE
        NOE_PLUGIN)

set_target_properties(IniConfiguration PROPERTIES PREFIX "")
set_target_properties(IniConfiguration PROPERTIES SUFFIX ".np")

install(TARGETS IniConfiguration RUNTIME DESTINATION "bin/plugins" LIBRARY DESTINATION "bin/plugins")
install(FILES "IniConfiguration.pconf" DESTINATION "bin/plugins")



