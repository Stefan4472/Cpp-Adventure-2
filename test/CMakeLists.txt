# Just to build the tests... Need to learn how to integrate this into the other CMakeLists.
cmake_minimum_required(VERSION 3.1)
project(
    CGameTest
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Add `-g` debug compilation command
# TODO: USE `TARGET` PROPERLY
#target_compile_options(CGame PRIVATE -g)
enable_testing()

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GTest REQUIRED)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(
    ../src/engine
    ../src/tiles
    ../src/objects
    ../src/sprites
    ../src/items
    ../src/drops
    ${Boost_INCLUDE_DIR} 
    ${SDL2_INCLUDE_DIR}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
)

# Recursively add all .cpp files in 'src'
file(GLOB_RECURSE SOURCES 
    "../src/engine/*.cpp"
    "../src/tiles/*.cpp"
    "../src/objects/*.cpp"
    "../src/sprites/*.cpp"
    "../src/items/*.cpp"
    "../src/drops/*.cpp"
)

add_executable(
    CGameTest 
    run_tests.cpp 
    ${SOURCES}
)

target_link_libraries(
    CGameTest
    ${Boost_LIBRARIES} 
    ${SDL2_LIBRARIES} 
    ${SDL2IMAGE_LIBRARIES}
    ${GTEST_LIBRARIES}
    pthread
    gtest
)