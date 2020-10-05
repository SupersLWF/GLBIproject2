#include<glew.h>
#include<glfw3.h>
#include<iostream>

#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class GLBIMat4transform
{
private:
	glm::mat4* modelTransfMat4;
	glm::mat4* modelTransfMat4Last;
	glm::mat4* modelTransfMat4Default;
	GLfloat SpinAngle;
	GLuint shaderID;
	void modelTransf(glm::mat4* TransfMat4);
public:

	void setSpinAngle(const GLfloat&);

	void ModelTransReset();
	void ModelTransUptolast();

	void modelScale();
	void modelRotate();
	void modelTranslate();


	//变换时，矩阵相乘最好是先缩放，在旋转，最后位移。


	//坐标变幻时，正好是反的，先model变换，也就是先变换顶点矩阵，再位移坐标空间，最后缩放（透视）坐标空间。
	//inline glm::mat4 modelcoord() { return modeltrance(translationMat4(), rotationMat4(), scaleMat4()); };
	inline glm::mat4 viewcoord() { return glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); };
	inline glm::mat4 projcoord() { return glm::perspective(glm::radians(45.0f), (GLfloat)(1000 / 700), 1.0f, 100.0f); };
  
public:
	GLBIMat4transform();
	GLBIMat4transform(GLuint* ShaderID);
	void uniform_settings();
};

