#ifndef IOMANAGER_H
#define IOMANAGER_H
#pragma once
#include <vector>
#include <string>
#include <fstream>
class IOmanager
{
    public:
        static bool readFileToBuffer(const std::string& filePath,std::vector<unsigned char>& buffer);
        IOmanager() = default;

    protected:

    private:
};

#endif // IOMANAGER_H
