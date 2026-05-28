cmake_minimum_required(VERSION 4.3)

project(Boannt)

find_package(SFML 3.1 REQUIRED COMPONENTS Graphics Audio Network)

add_library(random_engine src/core/random_engine.cpp)
add_library(perlin_noise src/core/perlin_noise.cpp)
add_library(world_lib src/world/chunk.cpp src/world/terrain_gen.cpp src/world/cave_gen.cpp)
add_library(blocks src/blocks/block.cpp src/blocks/BlockRegistry.cpp)
add_library(renderer src/renderer/renderBlock.cpp src/renderer/renderTileMap.cpp)

target_link_libraries(world_lib PRIVATE perlin_noise random_engine)
target_link_libraries(renderer PRIVATE blocks world_lib SFML::Graphics)


target_include_directories(perlin_noise PUBLIC src)
target_include_directories(world_lib PUBLIC src)
target_include_directories(random_engine PUBLIC src)
target_include_directories(blocks PUBLIC src)
target_include_directories(renderer PUBLIC src)


add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE world_lib perlin_noise renderer random_engine SFML::Graphics SFML::Audio SFML::Network)

