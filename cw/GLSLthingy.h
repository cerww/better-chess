#pragma once
#ifndef GLSLTHINGY_H
#define GLSLTHINGY_H
#include <string>
#include <iostream>
#include <cstring>
#include <GL/glew.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <GLFW/glfw3.h>

class GLSLthingy
{
    public:
        GLSLthingy();

        void compileshad(const std::string &vertfile,const std::string &fragfile);
        void compileshadSource(const std::string &vert,const std::string &frag);
        void linkshader();
        void addAttribute(const std::string& attribName);
        GLint getUniformLocate(const std::string& uniName);
        void use();
        void unuse();
    protected:

    private:

        void compleshady(const std::string &filepath,GLuint &ID);
        GLuint programID = 0;
        GLuint vertShadID = 0;
        GLuint fragShadID = 0;
        GLint numAttribs = 0;
};


#endif // GLSLTHINGY_H

