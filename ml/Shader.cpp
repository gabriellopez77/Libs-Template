#include "Shader.h"

#include "../glad/glad.h"

#include "fstream"
#include "sstream"
#include <iostream>

ml::Shader::Shader(const char* vertPath, const char* fragPath) {
	if (vertPath == nullptr)
		return;

	// leitura dos arquivos de shaders
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// abre os arquivos
	vShaderFile.open(vertPath);
	fShaderFile.open(fragPath);

	// le os arquivos
	std::stringstream vShaderStream, fShaderStream;
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();

	// fecha os arquivos
	vShaderFile.close();
	fShaderFile.close();

	// converte o conteudo dos arquivos em uma string
	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();

	// pega o ponteiro dos arquivos convertidos em string
	const char* vert = vertexCode.c_str();
	const char* frag = fragmentCode.c_str();


	// compila��o dos shaders
	unsigned int vertShader;
	unsigned int fragShader;

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vert, NULL);
	glCompileShader(vertShader);

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &frag, NULL);
	glCompileShader(fragShader);

	id = glCreateProgram();
	glAttachShader(id, vertShader);
	glAttachShader(id, fragShader);
	glLinkProgram(id);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	colorLoc = glGetUniformLocation(id, "color");
	modelLoc = glGetUniformLocation(id, "model");
	viewLoc = glGetUniformLocation(id, "view");
	alphaLoc = glGetUniformLocation(id, "alpha");
	useTextureLoc = glGetUniformLocation(id, "useTexture");
}