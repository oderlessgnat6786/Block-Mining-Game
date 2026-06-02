cmake_minimum_required(VERSION 4.3)

project(Boannt)

find_package(SFML 3.1 REQUIRED COMPONENTS Graphics Audio Network)

add_library(random_engine src/core/random_engine.cpp)
add_library(perlin_noise src/core/perlin_noise.cpp)
add_library(world_lib src/world/chunk.cpp src/world/terrain_gen.cpp src/world/cave_gen.cpp)
add_library(blocks src/blocks/block.cpp src/blocks/BlockRegistry.cpp)
add_library(renderer src/renderer/renderBlock.cpp src/renderer/renderTileMap.cpp src/renderer/camera.cpp src/renderer/renderPlayer.cpp src/renderer/renderWindow.cpp)
add_library(player src/entities/player.cpp)
add_library(filepaths src/core/filepaths.cpp)

target_link_libraries(world_lib PRIVATE perlin_noise random_engine)
target_link_libraries(renderer PRIVATE blocks world_lib SFML::Graphics filepaths)
target_link_libraries(player PRIVATE SFML::Graphics renderer)


target_include_directories(perlin_noise PUBLIC src)
target_include_directories(world_lib PUBLIC src)
target_include_directories(random_engine PUBLIC src)
target_include_directories(blocks PUBLIC src)
target_include_directories(renderer PUBLIC src)
target_include_directories(player PUBLIC src)


add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE filepaths world_lib perlin_noise renderer random_engine player SFML::Graphics SFML::Audio SFML::Network)
