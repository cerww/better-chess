#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include "vertex.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <map>
#include <memory>
#include <cstdlib>
#include <algorithm>
enum class glyphSortType{
NONE,FRONT_TO_BACK,BACK_TO_FRONT,TEXT
};
class Glyph{
public:
    Glyph(){};
    Glyph(const glm::vec4& dimensions,const glm::vec4& uv,GLuint text,Color colour,const float& depth);
    Glyph(const glm::vec4& dimensions,const glm::vec4& uv,GLuint text,Color colour,const float& depth,const float&angle);
    GLuint text;
    float depth;
    Vertex topLeft;
    Vertex botLeft;
    Vertex botRight;
    Vertex topRight;
private:
    glm::vec2 rotate(glm::vec2 dir,float angle);
};
struct renderBatchs{
    renderBatchs(GLuint Offset,GLuint NumVerts,GLuint Text):offset(Offset),numVerts(NumVerts),text(Text){};
    GLuint offset;
    GLuint numVerts;
    GLuint text;
};
class SpriteBatch
{
    public:
        SpriteBatch();
        virtual ~SpriteBatch();
        //void init();
        void begin(glyphSortType s=glyphSortType::TEXT);
        void end();
        void draw(glm::vec4 dimensions,glm::vec4 uv,GLuint text,Color colour,const float& depth,float angle);
        void draw(glm::vec4 dimensions,glm::vec4 uv,GLuint text,Color colour,const float& depth,glm::vec2 dir);
        void draw(glm::vec4 dimensions,glm::vec4 uv,GLuint text,Color colour,const float& depth);
        void renderBatch();

    protected:

    private:
        void createRenderBatches();
        void createVertArray();

        void sortGlyph();
        GLuint _vbo=0;
        GLuint _vao=0;
        glyphSortType _sortType;
        //std::vector<Glyph*> _glyphs;
        std::vector<Glyph*> _glyphPtrs;
        std::vector<Glyph> _glyphs;
        std::vector<renderBatchs> _renderBatchs;
};

#endif // SPRITEBATCH_H
