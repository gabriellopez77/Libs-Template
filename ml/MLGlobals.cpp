#include "MLGlobals.h"

#include "../glad/glad.h"

glm::vec2 TEXTURE_SPRITES_SIZE;

void bindVAO(int vao) {
	static int id = 0;

	if (id != vao) {
		id = vao;
		glBindVertexArray(id);
	}
}

void bindShader(int shader) {
	static int id = 0;

	if (id != shader) {
		id = shader;
		glUseProgram(id);
	}
}

void bindTexture(int texture) {
	static int id = 0;

	if (id != texture) {
		id = texture;
		glBindTexture(GL_TEXTURE_2D, id);
	}
}