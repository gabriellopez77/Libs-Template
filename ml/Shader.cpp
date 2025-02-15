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

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
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

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		// converte o conteudo dos arquivos em uma string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERRO AO LER ARQUIVOS\n";
	}

	const char* vert = vertexCode.c_str();
	const char* frag = fragmentCode.c_str();

	int compileStatus;
	char infoLog[512];

	// compila��o dos shaders
	unsigned int vertShader;
	unsigned int fragShader;

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vert, NULL);
	glCompileShader(vertShader);

	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus) {
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		std::cout << "VERT ERROR!!!\n" << infoLog << '\n';
		return;
	}

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &frag, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus) {
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "FRAG ERROR!!!\n" << infoLog << '\n';
		return;
	}

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