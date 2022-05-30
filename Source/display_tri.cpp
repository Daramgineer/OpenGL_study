#include <iostream>
#include"../include/glad/glad.h"
#include"../include/GLFW/glfw3.h"

// Vertex Shader �ҽ� (����)
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader �ҽ� (����)
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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

	//Vertex Shader ��ü ���� �� ���� ������
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Vertex Shader ��ü�� Vertex Shader source ȣ��
	glShaderSource(vertexShader, 1, & vertexShaderSource, NULL);
	//Vertex Shader�� code�� ������
	glCompileShader(vertexShader);


	//Fragment Shader ��ü ���� �� ���� ������
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Fragment Shader ��ü�� Fragment Shader source ȣ��
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Fragment Shader�� code�� ������
	glCompileShader(fragmentShader);

	//Shader Program ��ü ���� �� ���� ������
	GLuint shaderProgram = glCreateProgram();

	//Vertex & Fragment Shader�� Shader Program�� ����
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Shader Program�� ��� Shader ��ũ
	glLinkProgram(shaderProgram);

	//���̻� ��� �ʴ� Vertex & Fragment Shader ��ü ����
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Vertex ��ġ ����
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //��
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //��
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f //��
	};

	//Vertex Array Object & Vertex Buffer Object �����̳� ����
	GLuint VAO, VBO;

	//VAO�� VBO�� ���� 1���� ��ü ����
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//VAO�� current Vertex Array ��ü ����
	glBindVertexArray(VAO);

	//GL_ARRAY_BUFFER�� ������ ��ü�� VBO ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//VBO�� ���յ� vertices ���� ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//OpenGL�� VBO�� �ν��ϵ��� Vertex Ư�� ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//OpenGL�� Vertex�� ����ϵ��� Ư�� ����
	glEnableVertexAttribArray(0);

	//VAO & VBO�� 0���� ��� ���� �����ϴ� �Ǽ� ����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//��� ���� ����
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Back Buffer ���� �� ���ο� ���� ����
		glClear(GL_COLOR_BUFFER_BIT);
		//����ϴ� Shader Program OpenGL�� ����
		glUseProgram(shaderProgram);
		//OpenGL�� ����ϵ��� VAO ����
		glBindVertexArray(VAO);
		//GL_TRIANGLES�� ����Ͽ� �ﰢ�� �׸�
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//Back Buffer�� Front Buffer�� ��ȯ
		glfwSwapBuffers(window);
		//��� GLFW �̺�Ʈ ó��
		glfwPollEvents();
	}
	
	//������ �����ߴ� ��ü�� ����
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//���α׷� ���� �� Window����
	glfwDestroyWindow(window);

	//���α׷� ���� �� GLFW ����
	glfwTerminate();

	return 0;
}