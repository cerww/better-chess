#include "resourceManager.h"
#include <fstream>
#include <algorithm>
#include <utility>

const texture& resourceManager::getTexture(const std::string& dir){
    static std::unordered_map<std::string,const texture> m_texturesa;
    auto it= m_texturesa.find(dir);
    if(it==m_texturesa.end()){
        return (m_texturesa.insert(std::make_pair(dir,imgLoader::loadPNG(dir))).first->second);
    }
    return (it->second);
}

std::string resourceManager::getFileConts(const std::string& filePath){
	std::string fileContents;
	std::ifstream file(filePath,std::ios::in);
	file.seekg(0,std::ios::end);
	auto filesize = file.tellg();
	file.seekg(0,std::ios::beg);
    filesize -= file.tellg();
	fileContents.resize(filesize);
	file.read(&fileContents[0],filesize);
	file.close();
	return fileContents;
}
