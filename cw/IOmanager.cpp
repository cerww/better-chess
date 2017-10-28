#include "IOmanager.h"
#include <fstream>

bool IOmanager::readFileToBuffer(const std::string& filePath,std::vector<unsigned char>& buffer){
    std::ifstream file(filePath, std::ios::binary);
    if (file.fail()) {
        perror(filePath.c_str());
        return false;
    }
    file.seekg(0,std::ios::end);
    auto filesize = file.tellg();
    //buffer.resize(file.tellg());
    file.seekg(0,std::ios::beg);
    filesize -=file.tellg();
    buffer.resize(filesize);
    file.read((char*)&buffer[0],filesize);
    file.close();
    return true;
}


