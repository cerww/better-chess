#include "SpriteBatch.h"
#include <iostream>
SpriteBatch::SpriteBatch()
{
	createVertArray();
}

SpriteBatch::~SpriteBatch(){
    if(_vao)
        glDeleteVertexArrays(1,&_vao);
    if(_vbo)
        glDeleteBuffers(1,&_vbo);

}

void SpriteBatch::begin(glyphSortType s/*TEXTURE default */){
    _sortType=s;
    _renderBatchs.clear();
    _glyphs.clear();
}
void SpriteBatch::end(){

    _glyphPtrs.resize(_glyphs.size());
    for(unsigned x = 0;x<_glyphPtrs.size();++x){
        _glyphPtrs[x]=&_glyphs[x];
    }
    sortGlyph();

    createRenderBatches();
}
Glyph::Glyph(const glm::vec4& dimensions,const glm::vec4& uv,GLuint texty,Color colour,const float& depthy):
    text(texty),
    depth(depthy){
    topLeft.color=colour;
    topLeft.pos.x = dimensions.x;
    topLeft.pos.y = dimensions.y+dimensions.w;
    topLeft.setUV(uv.x,uv.y+uv.w);

    topRight.color=colour;
    topRight.pos.x = dimensions.x+dimensions.z;
    topRight.pos.y = dimensions.y+dimensions.w;
    topRight.setUV(uv.x+uv.z,uv.y+uv.w);

    botLeft.color=colour;
    botLeft.pos.x = dimensions.x;
    botLeft.pos.y = dimensions.y;
    botLeft.setUV(uv.x,uv.y);

    botRight.color=colour;
    botRight.pos.x = dimensions.x+dimensions.z;
    botRight.pos.y = dimensions.y;
    botRight.setUV(uv.x+uv.z,uv.y);
}
Glyph::Glyph(const glm::vec4& dimensions,const glm::vec4& uv,GLuint texty,Color colour,const float& depthy,const float& angle):
    text(texty),
    depth(depthy){
    glm::vec2 half(dimensions.z/2,dimensions.w/2);
    glm::vec2 tl(-half.x,half.y);
    glm::vec2 bl(-half.x,-half.y);
    glm::vec2 tr(half.x,half.y);
    glm::vec2 br(half.x,-half.y);

    tl = rotate(tl,angle)+half;
    bl = rotate(bl,angle)+half;
    br = rotate(br,angle)+half;
    tr = rotate(tr,angle)+half;

    topLeft.color=colour;
    topLeft.pos.x = dimensions.x+tl.x;
    topLeft.pos.y = dimensions.y+tl.y;
    topLeft.setUV(uv.x,uv.y+uv.w);

    topRight.color=colour;
    topRight.pos.x = dimensions.x+tr.x;
    topRight.pos.y = dimensions.y+tr.y;
    topRight.setUV(uv.x+uv.z,uv.y+uv.w);

    botLeft.color=colour;
    botLeft.pos.x = dimensions.x+bl.x;
    botLeft.pos.y = dimensions.y+bl.y;
    botLeft.setUV(uv.x,uv.y);

    botRight.color=colour;
    botRight.pos.x = dimensions.x+br.x;
    botRight.pos.y = dimensions.y+br.y;
    botRight.setUV(uv.x+uv.z,uv.y);
}
void SpriteBatch::draw(glm::vec4 dimensions,glm::vec4 uv,GLuint text,Color colour,const float& depth){
    _glyphs.emplace_back(dimensions,uv,text,colour,depth);
}
void SpriteBatch::draw(glm::vec4 dimensions,glm::vec4 uv,GLuint text,Color colour,const float& depth,float angle){
    _glyphs.emplace_back(dimensions,uv,text,colour,depth,angle);
}
void SpriteBatch::draw(glm::vec4 dimensions,glm::vec4 uv,GLuint text,Color colour,const float& depth,glm::vec2 dir){
    const glm::vec2 right(1.0,0.0);

    _glyphs.emplace_back(dimensions,uv,text,colour,depth,((dir.y<0.0f)?-1.0f:1.0f)*acos(glm::dot(glm::vec2(1.0f,0.0f),dir)));
}
glm::vec2 Glyph::rotate(glm::vec2 dir,float angle){
    return glm::vec2(dir.x*cos(angle)-dir.y*sin(angle),dir.x*sin(angle)-dir.y*cos(angle));
}
void SpriteBatch::renderBatch(){
    glBindVertexArray(_vao);
    for(int i = 0;i<(int)_renderBatchs.size();++i){
        glBindTexture(GL_TEXTURE_2D,_renderBatchs[i].text);
        glDrawArrays(GL_TRIANGLES,_renderBatchs[i].offset,_renderBatchs[i].numVerts);
    }
	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches(){
    if(_glyphs.empty()) return;
    std::vector<Vertex> vertices(_glyphs.size()*6);
    //renderBatch newBatch(0,6,_glyphs[0]->text);
    _renderBatchs.emplace_back(0,6,_glyphs[0].text);
    int cv = 0;
    vertices[cv++]=_glyphs[0].topLeft;
    vertices[cv++]=_glyphs[0].botLeft;
    vertices[cv++]=_glyphs[0].botRight;
    vertices[cv++]=_glyphs[0].botRight;
    vertices[cv++]=_glyphs[0].topRight;
    vertices[cv++]=_glyphs[0].topLeft;

    for(unsigned cg = 1;cg<_glyphs.size();++cg){
        if(_glyphs[cg].text!=_glyphs[cg-1].text){
            _renderBatchs.emplace_back(cg*6,6,_glyphs[cg].text);
        }else{
            _renderBatchs.back().numVerts+=6;
        }
        vertices[cv++]=_glyphs[cg].topLeft;
        vertices[cv++]=_glyphs[cg].botLeft;
        vertices[cv++]=_glyphs[cg].botRight;
        vertices[cv++]=_glyphs[cg].botRight;
        vertices[cv++]=_glyphs[cg].topRight;
        vertices[cv++]=_glyphs[cg].topLeft;
    }
    glBindBuffer(GL_ARRAY_BUFFER,_vbo);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),nullptr,GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,0,vertices.size()*sizeof(Vertex),vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void SpriteBatch::createVertArray(){
    if(!_vao)glGenVertexArrays(1,&_vao);
    glBindVertexArray(_vao);
    if(!_vbo)glGenBuffers(1,&_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,_vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,pos));
    glVertexAttribPointer(1,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(Vertex),(void*)offsetof(Vertex,color));
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,uv));
    glBindVertexArray(0);
}

void SpriteBatch::sortGlyph(){
    switch(_sortType){
        case glyphSortType::BACK_TO_FRONT:
            //std::stable_sort(_glyphPtrs.begin(),_glyphPtrs.end(),compareBackToFront);
            std::stable_sort(_glyphPtrs.begin(),_glyphPtrs.end(),[](Glyph* a,Glyph* b){return a->depth>b->depth;});
            break;
        case glyphSortType::FRONT_TO_BACK:
            //std::stable_sort(_glyphPtrs.begin(),_glyphPtrs.end(),compareFrontToBack);
            std::stable_sort(_glyphPtrs.begin(),_glyphPtrs.end(),[](Glyph* a,Glyph* b){return a->depth<b->depth;});
            break;
        case glyphSortType::TEXT:
            //std::stable_sort(_glyphPtrs.begin(),_glyphPtrs.end(),compareTexture);
            std::stable_sort(_glyphPtrs.begin(),_glyphPtrs.end(),[](Glyph* a,Glyph* b){return a->text<b->text;});
            break;
        case glyphSortType::NONE:
            break;
    }
}
/*
bool SpriteBatch::compareFrontToBack(const Glyph* a,const Glyph*b){
    return (a->depth>b->depth);
}
bool SpriteBatch::compareBackToFront(const Glyph*a,const Glyph*b){
    return a->depth<b->depth;
}
bool SpriteBatch::compareTexture(const Glyph*a,const Glyph*b){
    return a->text<b->text;
}
*/
