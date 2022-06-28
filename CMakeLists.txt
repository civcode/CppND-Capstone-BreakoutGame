cmake_minimum_required(VERSION 3.5)

project(BreakoutGame)

add_definitions(-std=c++17)

find_package(SDL2 REQUIRED)
find_package(Eigen3 REQUIRED NO_MODULE)

include_directories(
    ${CMAKE_SOURCE_DIR}/include    
    ${SDL2_INCLUDE_DIRS} 
    ${EIGEN3_INCLUDE_DIR}
)

file(GLOB game_SRC
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(BreakoutGame src/main.cpp ${game_SRC})

target_link_libraries(BreakoutGame ${SDL2_LIBRARIES} ${EIGEN3_LIBRARIES})
target_compile_options(BreakoutGame PRIVATE -w)
