#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <unordered_map>
#include "texture.h"
#include <string>
#include "imgLoader.h"
#include <utility>
#include <string>
class resourceManager
{
    public:
        static const texture& getTexture(const std::string&);
        static std::string getFileConts(const std::string&);
        //virtual ~resourceManager();

    protected:

    private:
        std::unordered_map<std::string,texture> m_textures;
};

#endif // RESOURCEMANAGER_H
