#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include "vertex.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <memory>
#include <cstdlib>
#include <algorithm>
#include "mathStuff.h"
#include <mutex>

enum class glyphSortType{
NONE,FRONT_TO_BACK,BACK_TO_FRONT,TEXT
};
class Glyph{
public:
    Glyph(){};
    Glyph(const glm::vec4& dimensions,const glm::vec4& uv,GLuint text,Color colour,float depth);
	Glyph(const glm::vec4& dimensions, const glm::vec4& uv, GLuint text, Color colour, float depth, math::radians angle);
	Glyph(const glm::vec4& dimensions, const glm::vec4& uv, GLuint text, Color colour, float depth, math::radians angle,const glm::vec2 rotationPoint);
    GLuint text;
    float depth;
    Vertex topLeft;
    Vertex botLeft;
    Vertex botRight;
    Vertex topRight;
private:
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
        void start(glyphSortType s=glyphSortType::TEXT);
        void stop();
		void draw(const glm::vec4 dimensions, const glm::vec4 uv, const GLuint text, const Color colour, const float depth, const math::radians angle,const glm::vec2 rotationPoint);
		void draw(const glm::vec4 dimensions, const glm::vec4 uv, const GLuint text, const Color colour, const float depth, const math::radians angle);
		void draw(const glm::vec4 dimensions, const glm::vec4 uv, const GLuint text, const Color colour, const float depth, const glm::vec2 dir);
		void draw(const glm::vec4 dimensions, const glm::vec4 uv, const GLuint text, const Color colour, const float depth);
        void renderBatch();

    protected:

    private:
        void createRenderBatches();
        void createVertArray();

        void sortGlyph();
		std::mutex m_mutex;
        GLuint _vbo=0;
        GLuint _vao=0;
        glyphSortType _sortType;
        //std::vector<Glyph*> _glyphs;
        std::vector<const Glyph*> _glyphPtrs;
        std::vector<Glyph> _glyphs;
        std::vector<renderBatchs> _renderBatchs;
};

#endif // SPRITEBATCH_H
