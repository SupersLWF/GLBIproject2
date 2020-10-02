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

public:	

	inline glm::mat4 translationMat4() { return glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0)); };
	inline glm::mat4 rotationMat4() { return glm::rotate(glm::mat4(1.0f), glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f)); };
	inline glm::mat4 scaleMat4() { return glm::scale(glm::mat4(1.0f), glm::vec3(0.7, 1.0, 1.0)); };

	inline glm::mat4 modeltrance(glm::mat4 Translation, glm::mat4 Rotation, glm::mat4 Scale) { return Translation * Rotation * Scale; };


	//变换时，矩阵相乘最好是先缩放，在旋转，最后位移
	//坐标变幻时，正好是反的，先model变换，也就是先变换顶点矩阵，再位移坐标空间，最后缩放（透视）坐标空间。
	
	inline glm::mat4 modelcoord() { return modeltrance(translationMat4(),rotationMat4(),scaleMat4()); };
	inline glm::mat4 viewcoord() { return glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); };
	inline glm::mat4 projcoord() { return glm::perspective(glm::radians(45.0f), (GLfloat)(1000/700), 1.0f, 100.0f); };

	void use();//绑定此shaderProgram

	//UNIFORM工具集,查询并填入UNIFORM
//protected:
//	virtual void setBool(const std::string& name, GLboolean value) = 0;
//	virtual void setInt(const std::string& name, GLint value) = 0;
//	virtual void setFloat(const std::string& name, GLfloat value) = 0;
	void uniform_settings();
};

