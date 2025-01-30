#pragma once

#include "../glm/glm.hpp"

#include <array>

namespace ml {
	class Slice {
	public:
		struct quad {
			glm::vec2 a, b, c, d;
		};

		static void init();

		void setNormalizedTex(int posX, int posY, int width, int height, int corner);
		void updateVertex(float sizeX, float sizeY);

		std::array<quad, 9> vertices;
		std::array<quad, 9> tex;

		static unsigned int vao, vbo, ebo, tex_vbo;
		static const unsigned int indices[54];
	};
}