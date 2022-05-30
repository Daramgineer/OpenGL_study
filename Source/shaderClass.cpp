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

	//Vertex Shader ��ü ���� �� ���� ������
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Vertex Shader ��ü�� Vertex Shader source ȣ��
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Vertex Shader�� code�� ������
	glCompileShader(vertexShader);


	//Fragment Shader ��ü ���� �� ���� ������
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Fragment Shader ��ü�� Fragment Shader source ȣ��
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Fragment Shader�� code�� ������
	glCompileShader(fragmentShader);

	//Shader Program ��ü ���� �� ���� ������
	ID = glCreateProgram();

	//Vertex & Fragment Shader�� Shader Program�� ����
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Shader Program�� ��� Shader ��ũ
	glLinkProgram(ID);

	//���̻� ��� �ʴ� Vertex & Fragment Shader ��ü ����
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