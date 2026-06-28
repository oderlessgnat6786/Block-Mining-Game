cmake_minimum_required(VERSION 4.3)

project(Boannt)

find_package(SFML 3.1 REQUIRED COMPONENTS Graphics Audio Network)

add_library(random_engine src/core/random_engine.cpp)
add_library(perlin_noise src/core/perlin_noise.cpp)
add_library(world_lib src/world/chunk.cpp src/world/terrain_gen.cpp src/world/cave_gen.cpp)
add_library(blocks src/blocks/block.cpp src/blocks/BlockRegistry.cpp)
add_library(renderer src/renderer/renderBlock.cpp src/renderer/renderTileMap.cpp src/renderer/camera.cpp src/renderer/renderPlayer.cpp src/renderer/renderWindow.cpp src/renderer/blockHighlights.cpp)
add_library(player src/entities/player.cpp)
add_library(loader src/core/filepaths.cpp src/core/configParser.cpp)
add_library(inputs src/input/keyboard_input.cpp src/input/mouse_input.cpp)
add_library(updater src/core/updater.cpp)
add_library(physics src/physics/collisions.cpp src/physics/movement.cpp src/physics/unitConverter.cpp)
add_library(gameplay src/core/tick.cpp)

target_link_libraries(world_lib PRIVATE perlin_noise random_engine)
target_link_libraries(renderer PRIVATE blocks world_lib SFML::Graphics loader inputs)
target_link_libraries(player PRIVATE SFML::Graphics renderer world_lib blocks)
target_link_libraries(inputs PRIVATE player SFML::Graphics renderer world_lib)
target_link_libraries(updater PRIVATE player SFML::Graphics world_lib physics)
target_link_libraries(gameplay PRIVATE updater player SFML::Graphics world_lib inputs)
target_link_libraries(physics PRIVATE player world_lib SFML::Graphics)

target_include_directories(perlin_noise PUBLIC src)
target_include_directories(world_lib PUBLIC src)
target_include_directories(random_engine PUBLIC src)
target_include_directories(blocks PUBLIC src)
target_include_directories(renderer PUBLIC src)
target_include_directories(player PUBLIC src)
target_include_directories(inputs PUBLIC src)
target_include_directories(physics PUBLIC src)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE loader gameplay world_lib renderer player SFML::Graphics SFML::Audio SFML::Network)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets

    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/config
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/config
)