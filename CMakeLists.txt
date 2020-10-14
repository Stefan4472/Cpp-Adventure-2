# Not great... But it works! I'm going to be trying to revisit this
# and learn more about CMake as I go.
cmake_minimum_required(VERSION 3.1)
project(
    CGame
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Add `-g` debug compilation command
# TODO: USE `TARGET` PROPERLY
#target_compile_options(CGame PRIVATE -g)
set(CMAKE_CXX_FLAGS "-g")

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(SDL2 REQUIRED)
INCLUDE(FindPkgConfig)
#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(
    src/engine
    src/tiles
    src/objects
    src/sprites
    src/items
    src/drops
    ${Boost_INCLUDE_DIR} 
    ${SDL2_INCLUDE_DIR}
    ${SDL2IMAGE_INCLUDE_DIRS}
)

# Recursively add all .cpp files in 'src'
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(
    CGame 
    src/main.cpp 
    ${SOURCES}
)

target_link_libraries(
    CGame 
    ${Boost_LIBRARIES} 
    ${SDL2_LIBRARIES} 
    ${SDL2IMAGE_LIBRARIES}
)