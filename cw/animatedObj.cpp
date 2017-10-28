#include "animatedObj.h"
#include <iostream>


void renderAnimatedObjects::render(const camera2D& cam){
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

void renderAnimatedObjects::drawObj(animatedObj* obj){
    //m_objs.push_back(obj);
    if(obj->currentAni==nullptr){
        return;
    }
	obj->update();
    spriteB.draw(obj->m_dims,obj->uv,obj->m_texture.id,Color(255,255,255,255),1.0f);
}

animatedObj::animatedObj(glm::vec4&& dims,const std::string& animationInfo):m_dims(dims){
    getAniInfo(animationInfo);
     //std::cout<<dims.x<<' '<<dims.y<<' '<<dims.z<<' '<<dims.w<<'\n';
}

animatedObj::animatedObj(glm::vec4& dims,const std::string& animationInfo):m_dims(dims){
    getAniInfo(animationInfo);
    //std::cout<<dims.x<<' '<<dims.y<<' '<<dims.z<<' '<<dims.w<<'\n';
}

renderAnimatedObjects::renderAnimatedObjects(){
    glslProg.compileshad("texture.vert","texture.frag");
    glslProg.addAttribute("vertPosition");
    glslProg.addAttribute("vertColor");
    glslProg.addAttribute("vertUV");

    glslProg.linkshader();

    //spriteB.init();
    spriteB.begin();
}

void animatedObj::setPart(const std::string& partName){
    auto it = m_animations.find(partName);
    if(it==m_animations.end()){
        std::cout<<partName<<std::endl;
        return;
    }
    currentAni = &m_animations[partName];
    m_currentFrame = 0;
    m_endingFrame = currentAni->num*currentAni->speed;

    uv.x = (currentAni->start%m_frameW)*1.0f/(float)(m_frameW);
    uv.y = (currentAni->start/m_frameW)*1.0f/(float)m_frameW;//uv.x+1.0f/(float)m_frameW;
    uv.z = 0+1.0f/(float)m_frameW;
    uv.w = 0+1.0f/(float)m_frameH;

    //std::cout<<uv.x<<" "<<uv.y<<" "<<uv.z<<" "<<uv.w<<'\n';
}

void animatedObj::update() {
	if (!currentAni) {
		return;
	}
	++m_currentFrame;
	if (m_currentFrame == m_endingFrame) {
		if (currentAni->mode == animationMode::REPEAT) {
			m_currentFrame = currentAni->start;
		}
		else if (currentAni->mode == animationMode::STAY) {
			--m_currentFrame;
		}
		else {
			m_currentFrame = 0;
			m_endingFrame = 0;
			currentAni = nullptr;
			m_currentPart = "";
			return;
		}//if(curr){}
	}

	uv.x = ((currentAni->start + (m_currentFrame / currentAni->speed)) % m_frameW)*1.0f / (float)(m_frameW);
	uv.y = ((currentAni->start + (m_currentFrame / currentAni->speed)) / m_frameW)*1.0f / (float)m_frameW;
}

void animatedObj::getAniInfo(const std::string& animationInfo) {
	try {
		unsigned ocurrent = 0;
		auto current = animationInfo.find('\n');

		//std::cout<<animationInfo.substr(0,current-ocurrent)<<std::endl;
		m_texture = std::move(resourceManager::getTexture(animationInfo.substr(0, current - ocurrent)));//imgLoader::loadPNG(animationInfo.substr(0,current-ocurrent));
		//std::cout<<"aaasd"<<std::endl;
		ocurrent = (unsigned)current + 1;
		current = animationInfo.find(' ', current + 1);
		m_frameW = (unsigned)atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());
		ocurrent = (unsigned)current + 1;
		current = animationInfo.find('\n', current + 1);
		m_frameH = atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());
		while (current < animationInfo.size() - 3) {

			ocurrent = (unsigned)current + 1;
			current = animationInfo.find(' ', current + 1);
			std::string aniName = animationInfo.substr(ocurrent, current - ocurrent);

			ocurrent = (unsigned)current + 1;
			current = animationInfo.find(' ', current + 1);
			int start = atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());

			ocurrent = (unsigned)current + 1;
			current = animationInfo.find(' ', current + 1);
			int num = atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());

			ocurrent = (unsigned)current + 1;
			current = animationInfo.find(' ', current + 1);
			animationMode m = (animationMode)atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());

			ocurrent = (unsigned)current + 1;
			current = animationInfo.find_first_of(" \n", current + 1);
			int speed = atoi(animationInfo.substr(ocurrent, current - ocurrent).c_str());

			//std::cout<<aniName<<" "<<start<<" "<<num<<" "<<(int)m<<" "<<speed<<'\n';
			m_animations.insert(std::make_pair(aniName, framey(start, num, m, speed)));
		}//currentAni = &m_animations.begin().second;
		//for(auto& i:m_animations){std::cout<<i.first<<std::endl;}
	}
	catch(...){
		//somehow crash
		//std::cout << e << std::endl;
		std::cout << animationInfo << " is not valid" << std::endl;
		currentAni = nullptr;
		return;
	}
}

void animatedObj::init(glm::vec4&& dims,const std::string& aniInfo){
    m_dims = dims;
    getAniInfo(aniInfo);
}

void animatedObj::init(glm::vec4& dims,const std::string& aniInfo){
    m_dims = dims;
    getAniInfo(aniInfo);
}
