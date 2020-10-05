#include<glew.h>
#include<glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
//GLM类库的大多数函数的包含文件

#include<iostream>

#define GLM_DEFINE \
private: glm::mat4 identifyMat4;\
public: inline glm::mat4 tranceMat4Getter(){return identifyMat4;}\
public: inline void tranceMatSetter(glm::mat4& temp){\
temp = glm::translate(temp, glm::vec3(0.5f, 0.5f, 0.5f));\
temp = glm::rotate(temp, glm::radians(90.0f), glm::vec3(0.0/*x*/, 0.0/*y*/, 1.0/*z*/));\
temp = glm::scale(temp, glm::vec3(0.5, 0.5, 0.5));}\
//注意：这里不能直接返回identifyMat4,因为稍后传入的引用是identifyMat4的引用。
//先缩放，再旋转，最后位移，但写的时候应该正好是反的，矩阵连乘的时候假定向量在最右边，也应该是从右向左乘，位移变换矩阵也还是在最左边

//translate是平移变换
//rotate是旋转变换，此处是绕z轴旋转
//scale是缩放变换，此处是x,y,z坐标均缩放0.5倍

//tranceMatSetter最终会将identifyMat4转换三个变换矩阵相乘的形式：translate*rotate*scale

#define GLMVAR_INIT identifyMat4 = glm::mat4(1.0f);

class GLBIshader
{
	GLM_DEFINE
public:
	GLuint parentID;//shaderProgramID
	GLuint shaderID[3];//shaderID
	GLBIshader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//由构造器读取并构建着色器
	void use();//绑定此shaderProgram
	void uniform_settings();

	//UNIFORM工具集,查询并填入UNIFORM
//protected:
//	//virtual void glmvarInit();
//	//如果要安置宏GLMVAR到GLBIshader，则必须使用此函数初始化GLMVAR。
//	virtual void setBool(const std::string& name, GLboolean value) = 0;
//	virtual void setInt(const std::string& name, GLint value) = 0;
//	virtual void setFloat(const std::string& name, GLfloat value) = 0;

};
