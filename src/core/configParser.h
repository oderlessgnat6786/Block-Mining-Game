#pragma once
#include <string>

class Engine_Constants
{
private:
    //  -------- ENGINE -------------

    // CHUNK
    inline static unsigned seed = 0;
    inline static int chunkHeight = 64;
    inline static int chunkWidth = 64;
    inline static int surfaceMin = 30;
    inline static int surfaceMax = 60;
    inline static int dirtMin = 2;
    inline static int dirtMax = 5;
    inline static int offsetX = 0;
    inline static int offsetY = 0;

    // WINDOW
    inline static int TILE_SIZE = 121;
    inline static std::string gameTitle = "Boannt";

    // PHYSICS
    inline static float GRAVITY = 30.53f;
    inline static float FALL_SPEED = 20.1f;
    inline static float safe_step = 30;

    // PLAYER
    inline static float health = 100;
    inline static float speed = 2;
    inline static float jumpPower = 2;
    inline static float miningSpeed = 35;

    inline static bool devMode = 0;

public:
    static void load();

    // GETTERS

    static int getChunkHeight();
    static int getChunkWidth();
    static int getSurfaceMin();
    static int getSurfaceMax();
    static int getDirtMin();
    static int getDirtMax();
    static int getOffsetX();
    static int getOffsetY();
    static int getTileSize();
    static const std::string &getGameTitle();
    static float getGravity();
    static float getFallSpeed();
    static float getSafeStep();
    static float getHealth();
    static float getSpeed();
    static float getJumpPower();
    static float getMiningSpeed();
    static bool getDevMode();
    static unsigned getSeed();
};

class User_Settings
{
private:
    inline static unsigned WINDOW_WIDTH = 1280;
    inline static unsigned WINDOW_HEIGHT = 1080;
    inline static unsigned FPS = 60;
    inline static bool VSYNC = 0;

    inline static unsigned MUSIC_VOLUME = 100;
    inline static unsigned SFX_VOLUME = 100;

    inline static bool DEV_MODE = 0;

public:
    static void load();
    static void save();
    static void restore_defaults();

    static int getBlockRadius();
    static unsigned getWindowWidth();
    static void setWindowWidth(unsigned width);
    static unsigned getWindowHeight();
    static void setWindowHeight(unsigned height);
    static unsigned getFps();
    static void setFps(unsigned fps);
    static bool getVsync();
    static void setVsync(bool vsync);
    static unsigned getMusicVolume();
    static void setMusicVolume(unsigned volume);
    static unsigned getSfxVolume();
    static void setSfxVolume(unsigned volume);
    static bool getDevMode();
    static void setDevMode(bool devMode);
};