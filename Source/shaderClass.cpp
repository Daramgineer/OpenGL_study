#include "../Headers/shaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Vertex Shader 객체 생성 및 참조 가져옴
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Vertex Shader 객체로 Vertex Shader source 호출
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Vertex Shader를 code에 컴파일
	glCompileShader(vertexShader);


	//Fragment Shader 객체 생성 및 참조 가져옴
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Fragment Shader 객체로 Fragment Shader source 호출
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Fragment Shader를 code에 컴파일
	glCompileShader(fragmentShader);

	//Shader Program 객체 생성 및 참조 가져옴
	ID = glCreateProgram();

	//Vertex & Fragment Shader를 Shader Program에 연결
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Shader Program에 모든 Shader 링크
	glLinkProgram(ID);

	//더이상 사용 않는 Vertex & Fragment Shader 객체 삭제
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}