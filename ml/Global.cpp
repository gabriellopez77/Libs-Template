#include "Global.h"

#include "../glad/glad.h"
#include "Sprite.h"

#include <iostream>

glm::vec2 SCREEN_SIZE(0.f);

glm::vec2 TEXTURE_SPRITES_SIZE;

void bindVAO(int vao) {
	static int id;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &id);
	if (id != vao)
		glBindVertexArray(vao);
}