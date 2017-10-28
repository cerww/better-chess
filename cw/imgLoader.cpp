#include "imgLoader.h"
#include "IOmanager.h"
#include "stdio.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "lodepng.h"

texture imgLoader::loadPNG(const std::string &path){
	texture tex = {};
    //std::vector<unsigned char> in;
    std::vector<unsigned char> outpic;
	/*
    if(!IOmanager::readFileToBuffer(path,in)){
        std::cout<<"4\n"<<std::endl;
        glfwTerminate();
    }*/
    int error = lodepng::decode(outpic,tex.width,tex.height,path.c_str());
    if(error){
		std::cout << "decondPNG failed with" << error << std::endl;
        glfwTerminate();
		return {};
    }
    glGenTextures(1,&(tex.id));
    glBindTexture(GL_TEXTURE_2D,tex.id);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,tex.width,tex.height,0,GL_RGBA,GL_UNSIGNED_BYTE,&(outpic[0]));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);
    return tex;
}
