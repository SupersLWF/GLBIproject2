#include "GLBIMat4transform.h"

void GLBIMat4transform::modelTransf(glm::mat4* TransfMat4)
{
		*TransfMat4 = glm::scale(*modelTransfMat4, glm::vec3(0.7, 1.0, 1.0));
		*TransfMat4 = glm::rotate(*modelTransfMat4, glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		*TransfMat4 = glm::translate(*modelTransfMat4, glm::vec3(0.0, 0.0, 0.0));
}

void GLBIMat4transform::setSpinAngle(const GLfloat& Angle)
{
	this->SpinAngle = Angle;
}

void GLBIMat4transform::ModelTransReset()
{
	*modelTransfMat4 = *modelTransfMat4Default;
}

void GLBIMat4transform::ModelTransUptolast()
{

}

void GLBIMat4transform::modelScale()
{
}//可能会对之前的modelTranslate产生影响，不过仍未测试

void GLBIMat4transform::modelRotate()
{
	if (SpinAngle == 0.0f)
		SpinAngle = 0.1f;
	*modelTransfMat4 = glm::rotate(*modelTransfMat4, glm::radians(SpinAngle), glm::vec3(1.0f, 1.0f, 1.0f));
}

void GLBIMat4transform::modelTranslate()
{
}

GLBIMat4transform::GLBIMat4transform()
{
	modelTransfMat4 = new glm::mat4(1.0f);
	modelTransfMat4Default = new glm::mat4(1.0f);
}

GLBIMat4transform::GLBIMat4transform(GLuint* ShaderID)
{
	modelTransfMat4 = new glm::mat4(1.0f);
	modelTransfMat4Default = new glm::mat4(1.0f);
	setSpinAngle(0.1f);
	modelTransf(modelTransfMat4);
	modelTransf(modelTransfMat4Default);
	this->shaderID = *ShaderID;
}

void GLBIMat4transform::uniform_settings()//私有函数在成员函数内部可见。
{
	//glUniformMatrix4fv(glGetUniformLocation(this->shaderID, "modelcoord"), 1, GL_FALSE, glm::value_ptr(modelcoord()));
	glUniformMatrix4fv(glGetUniformLocation(this->shaderID, "modelcoord"), 1, GL_FALSE, glm::value_ptr(*modelTransfMat4));
	glUniformMatrix4fv(glGetUniformLocation(this->shaderID, "viewcoord"), 1, GL_FALSE, glm::value_ptr(viewcoord()));
	glUniformMatrix4fv(glGetUniformLocation(this->shaderID, "projcoord"), 1, GL_FALSE, glm::value_ptr(projcoord()));
}
