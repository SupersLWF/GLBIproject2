#include "GLBIshader.h"
#include <io.h>
#include <sys/stat.h>

#define MaxShaderSize 2000
#define MaxLogSize 512

//void GLBIshader::glmvarInit()
//{
//}

GLBIshader::GLBIshader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	//读取文件

	//glmvarInit();
	GLMVAR_INIT
	tranceMatSetter(identifyMat4);

	char buf1[MaxShaderSize];
	FILE* vertexShader_file;
	errno_t err1 = 0;
	err1 = fopen_s(&vertexShader_file, vertexPath, "rb");
	if (err1 == 0)
	{
		GLint fileSize = _filelength(_fileno(vertexShader_file));
		GLint CONTER = fread_s(buf1, fileSize, fileSize, 1, vertexShader_file);
		fclose(vertexShader_file);
		strncpy_s(buf1, buf1, fileSize);
	}
	else {
		perror("fopen_s");
	}
	const GLchar* vertexShaderBuf = buf1;

	char buf2[MaxShaderSize];
	FILE* fragmentShader_file;
	errno_t err2 = NULL;
	err2 = fopen_s(&fragmentShader_file, fragmentPath, "rb");
	if (err2 == 0)
	{
		GLint fileSize = _filelength(_fileno(fragmentShader_file));
		GLint CONTER = fread_s(buf2, fileSize, fileSize, 1, fragmentShader_file);
		fclose(fragmentShader_file);
		strncpy_s(buf2, buf2, fileSize);
	}
	else {
		perror("fopen_s");
	}

	const GLchar* fragmentShaderBuf = buf2;


	//编译shader
	shaderID[0] = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderID[0], 1, &vertexShaderBuf, NULL);
	glCompileShader(shaderID[0]);

	//打印编译错误
	GLint success;
	GLchar infoLog1[MaxLogSize];
	glGetShaderiv(shaderID[0], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID[0], 512, NULL, infoLog1);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog1 << std::endl;
	};

	//编译shader
	shaderID[2] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderID[2], 1, &fragmentShaderBuf, NULL);
	glCompileShader(shaderID[2]);

	//打印编译错误
	GLchar infoLog2[MaxLogSize];
	glGetShaderiv(shaderID[2], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID[0], 512, NULL, infoLog2);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
	};

	//封装shader
	parentID = glCreateProgram();
	glAttachShader(parentID, shaderID[0]);
	glAttachShader(parentID, shaderID[2]);
	glLinkProgram(parentID);
}

void GLBIshader::use()
{
	glUseProgram(parentID);
}
 
void GLBIshader::uniform_settings() 
{	
	glUniformMatrix4fv(glGetUniformLocation(parentID, "TransMatex"), 1, GL_FALSE, glm::value_ptr(tranceMatGetter()));
	glUniform1i(glGetUniformLocation(parentID, "texture1"), 0);
	glUniform1i(glGetUniformLocation(parentID, "texture2"), 1);
}


