#include "drawableObj.h"

drawableObj::drawableObj(glm::vec4& dims,const std::string& file, Color color):m_dims(dims), m_color(color) {
    m_texture = resourceManager::getTexture(file);
}
drawableObj::drawableObj(glm::vec4&& dims,const std::string& file, Color color):m_dims(dims), m_color(color){
    m_texture = resourceManager::getTexture(file);
}

drawableObj::drawableObj(glm::vec4& dims, const texture& t, Color color) : m_dims(dims) ,m_texture(t), m_color(color) {
	//m_texture = resourceManager::getTexture(file);
}
drawableObj::drawableObj(glm::vec4&& dims, const texture& t, Color color) : m_dims(dims),m_texture(t), m_color(color) {
	//m_texture = resourceManager::getTexture(file);
}
/*
void drawableObj::setUVs(glm::vec4 newUVs){
    m_uv = newUVs;
}*/
void drawableObj::init(glm::vec4 dims,const std::string& file){
    m_dims = dims;
    m_texture = resourceManager::getTexture(file);
}

void drawableObj::move(glm::vec2 movea){
    m_dims.x += movea.x;
    m_dims.y += movea.y;
}

void drawableObj::draw(drawRenderer & renderer)const{
	renderer.spriteB.draw(m_dims,m_uv,m_texture.id,m_color,1.0f);
}

void drawRenderer::draw(const drawableObj* obj){
    spriteB.draw(obj->m_dims,obj->m_uv,obj->m_texture.id,obj->m_color,1.0f);
}

void drawRenderer::draw(const drawableObj& obj) {
	spriteB.draw(obj.m_dims, obj.m_uv, obj.m_texture.id, obj.m_color, 1.0f);
}

void drawRenderer::draw(const glm::vec4 a, const glm::vec4 b, const GLuint c, const Color d, GLfloat e){
	spriteB.draw(a, b, c, d, e);
}

void drawRenderer::draw(const glm::vec4 a, const glm::vec4 b, const GLuint c, const Color d, GLfloat e, math::radians angle){
	spriteB.draw(a, b, c, d, e, angle.angle);
}

void drawRenderer::render(const camera2D& cam){
    glslProg.use();

    spriteB.end();

    glActiveTexture(GL_TEXTURE0);
    GLint textlocate = glslProg.getUniformLocate("Text");
    glUniform1i(textlocate,0);

    GLint camLocate = glslProg.getUniformLocate("orthiMat");
    glm::mat4 abc = cam.getCamMatrix();
    glUniformMatrix4fv(camLocate,1,GL_FALSE,&abc[0][0]);

    spriteB.renderBatch();

    glslProg.unuse();

    spriteB.begin();
}
drawRenderer::drawRenderer(){
    glslProg.compileshad("texture.vert","texture.frag");
    glslProg.addAttribute("vertPosition");
    glslProg.addAttribute("vertColor");
    glslProg.addAttribute("vertUV");

    glslProg.linkshader();

    //spriteB.init();
    spriteB.begin();
}
