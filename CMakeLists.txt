cmake_minimum_required(VERSION 3.15 FATAL_ERROR) 
project(imgui_sfml CXX)

option(BUILD_SHARED_LIBS TRUE)

add_subdirectory(Dependencies)

add_library(imgui_sfml STATIC)

target_sources(imgui_sfml 
    PRIVATE 
        imgui_impl_sfml.cpp
        imgui_impl_sfml.h
)

target_link_libraries(imgui_sfml 
    PUBLIC 
        sfml-window
        sfml-system
        imgui
)

target_include_directories(imgui_sfml PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Dependencies/SFML/include)

add_executable(sample)

target_sources(sample PRIVATE main.cpp dumb_windows_function.cpp)

target_link_libraries(sample PUBLIC imgui imgui_sfml imgui_opengl3 opengl32.lib)

target_include_directories(sample PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Dependencies/SFML/include)