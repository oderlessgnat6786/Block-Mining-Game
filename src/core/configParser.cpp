#include "configParser.h"
#include "filepaths.h"
#include <toml++/toml.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
// ENGINE_CONSTANTS

void Engine_Constants::load()
{
    if (User_Settings::getDevMode())
    {
        devMode = 1;
        try
        {
            toml::table config = toml::parse_file(Filepaths::getConfig("engine_constants.toml"));


            seed = config["WorldGen"]["seed"].value_or(seed);
            chunkHeight = config["WorldGen"]["chunkHeight"].value_or(chunkHeight);
            chunkWidth = config["WorldGen"]["chunkWidth"].value_or(chunkWidth);
            surfaceMin = config["WorldGen"]["surfaceMin"].value_or(surfaceMin);
            surfaceMax = config["WorldGen"]["surfaceMax"].value_or(surfaceMax);
            dirtMin = config["WorldGen"]["dirtMin"].value_or(dirtMin);
            dirtMax = config["WorldGen"]["dirtMax"].value_or(dirtMax);

            offsetX = config["WorldGen"]["offsetX"].value_or(offsetX);
            offsetY = config["WorldGen"]["offsetY"].value_or(offsetY);

            GRAVITY = config["Physics"]["GRAVITY"].value_or(GRAVITY);
            FALL_SPEED = config["Physics"]["FALL_SPEED"].value_or(FALL_SPEED);
            safe_step = config["Physics"]["safe_step"].value_or(safe_step);

            health = config["Player"]["health"].value_or(health);
            speed = config["Player"]["speed"].value_or(speed);
            jumpPower = config["Player"]["jumpPower"].value_or(jumpPower);

            TILE_SIZE = config["Window"]["TILE_SIZE"].value_or(TILE_SIZE);
            gameTitle = config["Window"]["gameTitle"].value_or(gameTitle);
        }
        catch (const toml::parse_error &err)
        {
            // error
            std::cerr << err.description() << std::endl;
        }
    }
    GRAVITY = GRAVITY * TILE_SIZE;
    FALL_SPEED *= TILE_SIZE;
}

int Engine_Constants::getChunkHeight() { return chunkHeight; }
int Engine_Constants::getChunkWidth() { return chunkWidth; }
int Engine_Constants::getSurfaceMin() { return surfaceMin; }
int Engine_Constants::getSurfaceMax() { return surfaceMax; }
int Engine_Constants::getDirtMin() { return dirtMin; }
int Engine_Constants::getDirtMax() { return dirtMax; }
int Engine_Constants::getOffsetX() { return offsetX; }
int Engine_Constants::getOffsetY() { return offsetY; }
int Engine_Constants::getTileSize() { return TILE_SIZE; }
const std::string &Engine_Constants::getGameTitle() { return gameTitle; }
float Engine_Constants::getGravity() { return GRAVITY; }
float Engine_Constants::getFallSpeed() { return FALL_SPEED; }
float Engine_Constants::getSafeStep() { return safe_step; }
float Engine_Constants::getHealth() { return health; }
float Engine_Constants::getSpeed() { return speed; }
float Engine_Constants::getJumpPower() { return jumpPower; }
bool Engine_Constants::getDevMode() { return devMode; }
unsigned Engine_Constants::getSeed() { return seed; }
// USER_SETTINGS

void User_Settings::load()
{
    try
    {
        toml::table config = toml::parse_file(Filepaths::getConfig("user_settings.toml"));
        WINDOW_HEIGHT = config["Window"]["WINDOW_HEIGHT"].value_or(WINDOW_HEIGHT);
        WINDOW_WIDTH = config["Window"]["WINDOW_WIDTH"].value_or(WINDOW_WIDTH);
        FPS = config["Window"]["FPS"].value_or(FPS);
        VSYNC = config["Window"]["VSYNC"].value_or(VSYNC);

        MUSIC_VOLUME = config["Audio"]["MUSIC_VOLUME"].value_or(MUSIC_VOLUME);
        SFX_VOLUME = config["Audio"]["SFX_VOLUME"].value_or(SFX_VOLUME);

        DEV_MODE = config["Misc"]["DEV_MODE"].value_or(DEV_MODE);
    }
    catch (const toml::parse_error &err)
    {
        // error
        std::cerr << err.description() << std::endl;
    }
}

void User_Settings::save()
{
    toml::table config;
    config.insert("Window", toml::table{
                                {"WINDOW_HEIGHT", WINDOW_HEIGHT},
                                {"WINDOW_WIDTH", WINDOW_WIDTH},
                                {"FPS", FPS},
                                {"VSYNC", VSYNC}});

    config.insert("Audio", toml::table{
                               {"MUSIC_VOLUME", MUSIC_VOLUME},
                               {"SFX_VOLUME", SFX_VOLUME}});

    config.insert("Misc", toml::table{{"DEV_MODE", DEV_MODE}});

    std::ofstream file(Filepaths::getConfig("user_settings.toml"));
    if (file.is_open())
    {
        file << config;
        file.close();
    }
}

void User_Settings::restore_defaults()
{
    WINDOW_WIDTH = 1280;
    WINDOW_HEIGHT = 1080;
    FPS = 60;
    VSYNC = 0;

    MUSIC_VOLUME = 100;
    SFX_VOLUME = 100;

    DEV_MODE = 0;
}

int User_Settings::getBlockRadius()
{
    int maxDimension = std::max(WINDOW_HEIGHT, WINDOW_WIDTH);
    return (maxDimension / Engine_Constants::getTileSize()) / 2 + 2;
}

unsigned User_Settings::getWindowWidth() { return WINDOW_WIDTH; }
void User_Settings::setWindowWidth(unsigned width) { WINDOW_WIDTH = width; }

unsigned User_Settings::getWindowHeight() { return WINDOW_HEIGHT; }
void User_Settings::setWindowHeight(unsigned height) { WINDOW_HEIGHT = height; }

unsigned User_Settings::getFps() { return FPS; }
void User_Settings::setFps(unsigned fps) { FPS = fps; }

bool User_Settings::getVsync() { return VSYNC; }
void User_Settings::setVsync(bool vsync) { VSYNC = vsync; }

unsigned User_Settings::getMusicVolume() { return MUSIC_VOLUME; }
void User_Settings::setMusicVolume(unsigned volume) { MUSIC_VOLUME = volume; }

unsigned User_Settings::getSfxVolume() { return SFX_VOLUME; }
void User_Settings::setSfxVolume(unsigned volume) { SFX_VOLUME = volume; }

bool User_Settings::getDevMode() { return DEV_MODE; }
void User_Settings::setDevMode(bool devMode) { DEV_MODE = devMode; }
