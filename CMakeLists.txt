cmake_minimum_required(VERSION 3.29)
project(diretoryDescriptionGenerator)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include/imgui)
include_directories(include/imgui/backends)
include_directories(include/SDL3)
include_directories(include)

aux_source_directory(. BUILD_SRC)
aux_source_directory(include/imgui BUILD_SRC)
set(EXTRA_SRC
    include/imgui/backends/imgui_impl_sdl3.cpp
    include/imgui/backends/imgui_impl_opengl3.cpp
    include/imgui/misc/cpp/imgui_stdlib.cpp
)
aux_source_directory(include/SDL3 a)
message("buildfile:" ${BUILD_SRC} )
find_library(SDL3_STATIC_LIB 
    NAMES libSDL3 SDL3 
    PATHS ${CMAKE_SOURCE_DIR}/lib 
    NO_DEFAULT_PATH 
)
if(NOT SDL3_STATIC_LIB)
    message(FATAL_ERROR "SDL3静态库未找到！请检查lib目录下是否有SDL3-static.lib")
endif()

link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(DDG ${BUILD_SRC} ${EXTRA_SRC})
target_compile_definitions(DDG PRIVATE libSDL3)
target_link_libraries(DDG SDL3 opengl32)
# file(COPY bin/SDL3.dll DESTINATION /)
