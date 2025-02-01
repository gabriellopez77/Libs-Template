#pragma once

#include "../glm/glm.hpp"

#include <array>

namespace ml {
	struct quad {
		glm::vec2 a, b, c, d;
	};

	class Slice {
	public:
		Slice(float x, float y);

		static void init();

		void setNormalizedTex(int posX, int posY, int width, int height, int corner);
		void setVertexSize(float sizeX, float sizeY);

		std::array<quad, 9> vertices;
		std::array<quad, 9> tex;
		float boardSize;

		static unsigned int vao, vbo, ebo, tex_vbo;
		static const unsigned int indices[54];

	private:
		glm::vec2 size = glm::vec2(0.f);
	};
}