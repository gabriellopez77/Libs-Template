#include "MLGlobals.h"

#include "../glad/glad.h"

glm::vec2 TEXTURE_SPRITES_SIZE;

void bindVAO(int vao) {
	static int id;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &id);
	if (id != vao)
		glBindVertexArray(vao);
}

void bindShader(int shader) {
	static int id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	if (shader != id)
		glUseProgram(shader);
}

void bindTexture(int texture) {
	static int id;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &id);
	if (id != texture)
		glBindTexture(GL_TEXTURE_2D, texture);
}