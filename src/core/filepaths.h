#pragma once

#include <filesystem>
#include <string>

class Filepaths {
    private:
        static std::filesystem::path proot;
    public:
        static void init(const std::string& path);
        static std::string getAsset(std::string path);
};