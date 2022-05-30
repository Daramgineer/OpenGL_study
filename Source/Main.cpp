#include <iostream>
#include"../include/glad/glad.h"
#include"../include/GLFW/glfw3.h"

#include "../Headers/shaderClass.h"
#include "../Headers/VAO.h"
#include "../Headers/VBO.h"
#include "../Headers/EBO.h"

//Vertex 위치 지정
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //좌
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //우
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //상
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //안쪽 좌
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //안쪽 우
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f //안쪽 하
};

GLuint indices[] =
{
	0, 3, 5, //하단 좌측 삼각형 정점
	3, 2, 4, //하단 우측 삼각형 정점
	5, 4, 1 //상단 삼각형 정점
};


int main()
{
	//GLFW 초기화
	glfwInit();

	//OpenGL 사용버전 GLFW 전달
	//OpenGL 3.3 사용
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//CORE profile 사용을 GLFW 전달
	//modern functions 사용 가능
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//800 x 800 픽셀의 FirstWindow이름 GLFWwindow 생성
	GLFWwindow* window = glfwCreateWindow(800, 800, "FirstWindow", NULL, NULL);

	//에러 예외처리
	if (window == NULL)
	{
		std::cout << "Failed to creat GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//current context에 window 연결
	glfwMakeContextCurrent(window);

	//GLAD를 호출해서 OpenGL 구성
	gladLoadGL();

	//window창에서 OpenGL의 Viewport 지정
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
		//배경 색상 정의
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Back Buffer 정리 및 새로운 색상 전달
		glClear(GL_COLOR_BUFFER_BIT);
		//사용하는 Shader Program OpenGL에 전달
		shaderProgram.Activate();
		//OpenGL이 사용하도록 VAO 결합
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//Back Buffer를 Front Buffer와 교환
		glfwSwapBuffers(window);
		//모든 GLFW 이벤트 처리
		glfwPollEvents();
	}

	//위에서 생성했던 객체들 삭제
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//프로그램 종료 전 Window삭제
	glfwDestroyWindow(window);
	//프로그램 종료 전 GLFW 종료
	glfwTerminate();

	return 0;
}