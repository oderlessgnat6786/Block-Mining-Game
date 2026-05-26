cmake_minimum_required(VERSION 4.3)

project(Boannt)

find_package(SFML 3.1 REQUIRED COMPONENTS Graphics Audio Network)

add_library(random_engine src/core/random_engine.cpp)
add_library(perlin_noise src/core/perlin_noise.cpp)
add_library(world_lib src/world/chunk.cpp src/world/terrain_gen.cpp src/world/cave_gen.cpp)

target_link_libraries(world_lib PRIVATE perlin_noise random_engine)

target_include_directories(perlin_noise PUBLIC src)
target_include_directories(world_lib PUBLIC src)
target_include_directories(random_engine PUBLIC src)


add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE world_lib perlin_noise random_engine SFML::Graphics SFML::Audio SFML::Network)

add_executable(SFMLexe src/renderer/window.cpp)
target_link_libraries(SFMLexe PRIVATE SFML::Graphics SFML::Audio SFML::Network)

