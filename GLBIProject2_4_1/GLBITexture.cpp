//#include "GLBITexture.h"
//GLint GLBITexture::TextureBlank = -1;
//
//GLBITexture::GLBITexture(const char* filepath, const char* textureNameInShader, GLuint ID, GLuint ShaderID)
//{
//	TextureBlank++;
//	this->TextureID = ID;
//	strcpy(this->TextureUnifName, textureNameInShader);
//	glGenTextures(1, &TextureID);
//	glActiveTexture(GL_TEXTURE0);
//	//栏位激活后，先行绑定的纹理ID，会使用当前激活的栏位
//	glBindTexture(GL_TEXTURE_2D, TextureID);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true);
//	GLubyte* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
//
//
//	//创建纹理文件
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);//调用GL准备好全级别的 多级纹理过滤。
//	}
//	else
//	{
//		std::cerr << "stb_texture_load_null" << std::endl;
//	}
//	stbi_image_free(data);
//
//}
//
//void GLBITexture::uniform_settings()
//{
//	glUniform1i(glGetUniformLocation(TextureID, TextureUnifName), TextureBlank);
//}
