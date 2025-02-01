#pragma once

#include "../glm/glm.hpp"

constexpr float VERTICES[] = {
	 -0.5f,  -0.5f, // top right
	 -0.5f,  0.5f, // bottom right
	  0.5f,  0.5f, // bottom left
	  0.5f,  -0.5f, // top left
};

constexpr unsigned int INDICES[6] = {
	0, 1, 3,
	1, 2, 3
};

extern glm::vec2 TEXTURE_SPRITES_SIZE;

extern void bindVAO(int vao);
extern void bindShader(int shader);
extern void bindTexture(int texture);