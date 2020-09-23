
#include<glew.h>
#include<glfw3.h>
#include<iostream>



class GLBIshader
{
public:
	GLuint parentID;//shaderProgramID
	GLuint shaderID[3];//shaderID
	GLBIshader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//由构造器读取并构建着色器

	void use();//绑定此shaderProgram

	//UNIFORM工具集,查询并填入UNIFORM
	//void setBool(const std::string& name, GLboolean value);
	//void setInt(const std::string& name, GLint value);
	//void setFloat(const std::string& name, GLfloat value);
};

