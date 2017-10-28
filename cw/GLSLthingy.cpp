#include "GLSLthingy.h"
GLSLthingy::GLSLthingy() {}

void GLSLthingy::compileshad(const std::string &vertfile, const std::string &fragfile) {
	programID = glCreateProgram();
	vertShadID = glCreateShader(GL_VERTEX_SHADER);
	fragShadID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!vertShadID) {
		printf("0a");
		glfwTerminate();
	}
	if (!fragShadID) {
		printf("0b");
		glfwTerminate();
	}
	/*
	std::ifstream vertFilePath(vertfile.c_str());
	std::string vertFileConts="";
	std::string line = "";
	while(std::getline(vertFilePath,line))
	vertFileConts+=line+"\n";
	vertFilePath.close();
	compleshady(vertFileConts,vertShadID);
	//std::cout<<vertFileConts<<'\n';

	std::ifstream fragFilePath(fragfile.c_str());
	std::string fragFileConts="";//use same var so i take up less memory. faster?
	line = "";
	while(std::getline(fragFilePath,line))
	fragFileConts+=line+"\n";
	fragFilePath.close();
	//std::cout<<fragFileConts<<'\n';
	compleshady(fragFileConts,fragShadID);*/
	compleshady(vertfile, vertShadID);
	compleshady(fragfile, fragShadID);
}
void GLSLthingy::compileshadSource(const std::string&vert, const std::string&frag) {
	programID = glCreateProgram();
	vertShadID = glCreateShader(GL_VERTEX_SHADER);
	fragShadID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!vertShadID) {
		printf("0a");
		glfwTerminate();
	}
	if (!fragShadID) {
		printf("0b");
		glfwTerminate();
	}
	compleshady(vert, vertShadID);
	compleshady(frag, fragShadID);
}
void GLSLthingy::compleshady(const std::string &path, GLuint &ID) {

	std::ifstream vertFilePath(path.c_str());
	std::string vertfil = "";
	std::string line = "";
	while (std::getline(vertFilePath, line))vertfil += line + "\n";
	vertFilePath.close();

	//std::cout<<vertfil<<std::endl;//<<vertfil.c_str();
	//std::cout<<path<<std::endl;
	//const char* ContPtr = path.c_str();
	const char* ContPtr = vertfil.c_str();
	glShaderSource(ID, 1, &ContPtr, nullptr);
	glCompileShader(ID);
	GLint success = 0;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint maxl = 0;
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &maxl);
		std::vector<char> errorLog(maxl);
		glGetShaderInfoLog(ID, maxl, &maxl, &errorLog[0]);
		glDeleteShader(ID);
		printf("%s\n", &errorLog[0]);
		printf("1\n");
		glfwTerminate();
	}
}
void GLSLthingy::linkshader() {
	glAttachShader(programID, vertShadID);
	glAttachShader(programID, fragShadID);
	glLinkProgram(programID);
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxl = 0;
		glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &maxl);
		std::vector<GLchar> errorLog(maxl);
		glGetShaderInfoLog(programID, maxl, &maxl, &errorLog[0]);
		glDeleteProgram(programID);
		glDeleteShader(vertShadID);
		glDeleteShader(fragShadID);
		printf("%s\n", &(errorLog[0]));
		printf("2\n");
		glfwTerminate();
	}
	glDetachShader(programID, vertShadID);
	glDetachShader(programID, fragShadID);
	glDeleteShader(vertShadID);
	glDeleteShader(fragShadID);
}
void GLSLthingy::addAttribute(const std::string& attribName) {
	glBindAttribLocation(programID, numAttribs++, attribName.c_str());
	//std::cout<<numAttribs<<std::endl;
}

void GLSLthingy::use() {
	glUseProgram(programID);
	for (int i = 0; i<numAttribs; ++i)
		glEnableVertexAttribArray(i);
	//std::cout<<programID<<std::endl;
}
void GLSLthingy::unuse() {
	glUseProgram(0);
	for (int i = 0; i<numAttribs; ++i)
		glDisableVertexAttribArray(i);
}
GLint GLSLthingy::getUniformLocate(const std::string& uniName) {
	GLint l = glGetUniformLocation(programID, uniName.c_str());
	if ((unsigned)l == GL_INVALID_INDEX) {
		printf("3\n %s was not found", &uniName[0]);
		glfwTerminate();
	}
	return l;
}

