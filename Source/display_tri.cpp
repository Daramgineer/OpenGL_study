#include <iostream>
#include"../include/glad/glad.h"
#include"../include/GLFW/glfw3.h"

// Vertex Shader 소스 (정점)
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader 소스 (색상)
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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

	//Vertex Shader 객체 생성 및 참조 가져옴
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Vertex Shader 객체로 Vertex Shader source 호출
	glShaderSource(vertexShader, 1, & vertexShaderSource, NULL);
	//Vertex Shader를 code에 컴파일
	glCompileShader(vertexShader);


	//Fragment Shader 객체 생성 및 참조 가져옴
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Fragment Shader 객체로 Fragment Shader source 호출
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Fragment Shader를 code에 컴파일
	glCompileShader(fragmentShader);

	//Shader Program 객체 생성 및 참조 가져옴
	GLuint shaderProgram = glCreateProgram();

	//Vertex & Fragment Shader를 Shader Program에 연결
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Shader Program에 모든 Shader 링크
	glLinkProgram(shaderProgram);

	//더이상 사용 않는 Vertex & Fragment Shader 객체 삭제
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Vertex 위치 지정
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //좌
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //우
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f //상
	};

	//Vertex Array Object & Vertex Buffer Object 컨테이너 생성
	GLuint VAO, VBO;

	//VAO와 VBO에 각각 1개의 객체 생성
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//VAO와 current Vertex Array 객체 결합
	glBindVertexArray(VAO);

	//GL_ARRAY_BUFFER로 지정한 객체에 VBO 결합
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//VBO에 결합된 vertices 정보 전달
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//OpenGL이 VBO를 인식하도록 Vertex 특성 전달
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//OpenGL이 Vertex를 사용하도록 특성 전달
	glEnableVertexAttribArray(0);

	//VAO & VBO를 0으로 묶어서 이후 수정하는 실수 방지
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//배경 색상 정의
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Back Buffer 정리 및 새로운 색상 전달
		glClear(GL_COLOR_BUFFER_BIT);
		//사용하는 Shader Program OpenGL에 전달
		glUseProgram(shaderProgram);
		//OpenGL이 사용하도록 VAO 결합
		glBindVertexArray(VAO);
		//GL_TRIANGLES를 사용하여 삼각형 그림
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//Back Buffer를 Front Buffer와 교환
		glfwSwapBuffers(window);
		//모든 GLFW 이벤트 처리
		glfwPollEvents();
	}
	
	//위에서 생성했던 객체들 삭제
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//프로그램 종료 전 Window삭제
	glfwDestroyWindow(window);

	//프로그램 종료 전 GLFW 종료
	glfwTerminate();

	return 0;
}