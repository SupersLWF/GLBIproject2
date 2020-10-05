#include<glew.h>
#include<glfw3.h>
#include<iostream>

#include <math.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>



class GLBIshader
{
public:
	GLuint parentID;//shaderProgramID
	GLuint shaderID[3];//shaderID
	GLBIshader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//由构造器读取并构建着色器

protected:


public:
	void use();//绑定此shaderProgram

	//UNIFORM工具集,查询并填入UNIFORM
//protected:
//	virtual void setBool(const std::string& name, GLboolean value) = 0;
//	virtual void setInt(const std::string& name, GLint value) = 0;
//	virtual void setFloat(const std::string& name, GLfloat value) = 0;
	void uniform_settings();
};

