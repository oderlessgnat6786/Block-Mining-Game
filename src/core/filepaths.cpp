#include "filepaths.h"
#include <filesystem>
#include <string>

std::filesystem::path Filepaths::proot;

void Filepaths::init(const std::string& path){
  
    std::filesystem::path execPath = std::filesystem::canonical(path);
    Filepaths::proot = execPath.parent_path();
}

std::string Filepaths::getAsset(std::string assetPath){
    return (Filepaths::proot / "assets" / assetPath).string();
}

std::string Filepaths::getConfig(std::string assetPath){
    return (Filepaths::proot / "config" / assetPath).string();
}
