#include <iostream>
#include"../include/glad/glad.h"
#include"../include/GLFW/glfw3.h"

#include "../Headers/shaderClass.h"
#include "../Headers/VAO.h"
#include "../Headers/VBO.h"
#include "../Headers/EBO.h"

//Vertex ��ġ ����
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //��
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //��
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //��
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //���� ��
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //���� ��
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f //���� ��
};

GLuint indices[] =
{
	0, 3, 5, //�ϴ� ���� �ﰢ�� ����
	3, 2, 4, //�ϴ� ���� �ﰢ�� ����
	5, 4, 1 //��� �ﰢ�� ����
};


int main()
{
	//GLFW �ʱ�ȭ
	glfwInit();

	//OpenGL ������ GLFW ����
	//OpenGL 3.3 ���
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//CORE profile ����� GLFW ����
	//modern functions ��� ����
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//800 x 800 �ȼ��� FirstWindow�̸� GLFWwindow ����
	GLFWwindow* window = glfwCreateWindow(800, 800, "FirstWindow", NULL, NULL);

	//���� ����ó��
	if (window == NULL)
	{
		std::cout << "Failed to creat GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//current context�� window ����
	glfwMakeContextCurrent(window);

	//GLAD�� ȣ���ؼ� OpenGL ����
	gladLoadGL();

	//windowâ���� OpenGL�� Viewport ����
	//x=0, y=0, to x=800, y=800
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	
	//Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//��� ���� ����
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Back Buffer ���� �� ���ο� ���� ����
		glClear(GL_COLOR_BUFFER_BIT);
		//����ϴ� Shader Program OpenGL�� ����
		shaderProgram.Activate();
		//OpenGL�� ����ϵ��� VAO ����
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//Back Buffer�� Front Buffer�� ��ȯ
		glfwSwapBuffers(window);
		//��� GLFW �̺�Ʈ ó��
		glfwPollEvents();
	}

	//������ �����ߴ� ��ü�� ����
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//���α׷� ���� �� Window����
	glfwDestroyWindow(window);
	//���α׷� ���� �� GLFW ����
	glfwTerminate();

	return 0;
}