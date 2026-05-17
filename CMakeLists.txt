cmake_minimum_required(VERSION 3.13)

set(GEODE_DONT_SET_TARGETS ON)
find_package(Geode REQUIRED)

project(ia_editor_helper)

add_geode_mod(
    ia_editor_helper
    VERSION 1.0.0
    CONTAINS_LOADER
    
    SOURCES
        src/main.cpp
)
