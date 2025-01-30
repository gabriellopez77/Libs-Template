#pragma once

#include "../glm/glm.hpp"

constexpr float VERTICES[] = {
	 0.0f,  0.0f, // top right
	 0.0f,  1.0f, // bottom right
	 1.0f,  1.0f, // bottom left
	 1.0f,  0.0f, // top left
};

constexpr unsigned int INDICES[6] = {
	0, 1, 3,
	1, 2, 3
};

constexpr glm::vec2 SCREEN_SIZE(600.f, 800.f);

extern glm::vec2 TEXTURE_SPRITES_SIZE;
extern float SLICE_BOARD_SIZE;