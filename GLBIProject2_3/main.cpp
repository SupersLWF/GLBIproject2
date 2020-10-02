#include<glew.h>
#include<glfw3.h>
#include<iostream>
#include"GLBIshader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//库文件只是一个头文件，stb_image.h，如要使用此头文件，必须以此格式在前添加宏 STB_IMAGE_IMPLEMENTATION

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int hellowindow();

GLfloat vertices[] = {
	//     ---- 位置 ----     - 纹理坐标 -
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // 右上
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // 左上
};
GLint indices[]{
	0, 1, 2,
	2, 3, 0
};


int main() {
	hellowindow();
	return 0;
}

int hellowindow(){
	std::cout << "HELLO! WINDOW";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(1000,700,"test",NULL,NULL);

	if (window == NULL)
	{
		std::cerr << "window create fail!";
		glfwTerminate();
		return -1;
	}



	
	glfwMakeContextCurrent(window);
	

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	glewExperimental = true;

	
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "glewInit fail";
		glfwTerminate();
		return -1;
	}
	//加载shader
	GLBIshader shader("./shader/OpenGLPersetVertexShader(simple).gls", "./shader/OpenGLPersetFragmentShader(simple).gls");
	
	


	//初始化VAO，VBO， EBO
	GLuint VAO;  
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);   

	
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//从当前绑定的VBO挖掘数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3*sizeof(GLfloat)));//UV
	glEnableVertexAttribArray(1);


	//创建材质ID
	GLuint texture1,texture2;


	//为ID分配空间，激活一个栏位(单一材质时默认使用0号材质栏位)，将ID指定的材质空间与GL_TEXTURE_2D标签绑定。
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE0);
	//栏位激活后，先行绑定的纹理ID，会使用当前激活的栏位
	glBindTexture(GL_TEXTURE_2D, texture1);


	//设置当前与GL_TEXTURE_2D绑定的纹理ID的环绕方式，以及过滤方式，单次绘制仅需设置一次
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//加载纹理源文件
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	GLubyte* data = stbi_load("./texture/container.jpg", &width, &height, &nrChannels, 0);


	//创建纹理文件
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);//调用GL准备好全级别的 多级纹理过滤。
	}
	else
	{
		std::cerr << "stb_texture_load_null" << std::endl;
	}
	stbi_image_free(data);
	


	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE1); //可以通过GL_TEXTURE0 + 8的方式获得GL_TEXTURE8



	glBindTexture(GL_TEXTURE_2D, texture2);//将id = texture的存储空间与GL_TEXTURE_2D标签绑定，并使用序号较小的槽位存放该材质。
										  //一会向GL_TEXTURE_2D汇入纹理时，就会直接存入id = texture的texture类型存储空间。

	//设置当前绑定纹理的环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("./texture/lalala.png", &width, &height, &nrChannels, 0);

	//生成纹理
	if (data) {
		glTexImage2D(GL_TEXTURE_2D,     //要生成的纹理使用的 纹理源文件存储的栏位
			0, GL_RGBA,          //多级渐远纹理的级别？  生成的纹理包含的通道数
			width, height,      //最终纹理的宽度和高度，为了兼容性，以及为低性能设备考虑，一般设置为长宽相等，或长宽比为2的级数倍
			0, GL_RGBA, 			//忽略(始终为0)，源图的格式（通道数）
			GL_UNSIGNED_BYTE, 	//源图的数据类型
			data);				//源图数据（指针）

		glGenerateMipmap(GL_TEXTURE_2D);//为该栏位的纹理创建全部级别的多级渐远纹理。
		//或者反复调用上面的glTexImage2D也可以手动创建每一级渐远纹理，
		//只要调整第二个参数就可以生成不同级别的多级渐远纹理
		//基本级别“0”就是不创建多级渐远纹理,仅使用原始贴图


	}else{//如果加载成功，则data内至少是有值的。
		std::cerr << "stb_texture_load_null" << std::endl;
	}
	stbi_image_free(data);
	//OpenGL根据源图生成纹理后，源图就不需要了。


	


	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		shader.uniform_settings();

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	
	{
		glfwSetWindowShouldClose(window, true);
	}
}; 