#pragma once

#include "../glm/glm.hpp"

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

		quad vertices[9];
		quad tex[9];
		float boardSize = 0.f;

		static unsigned int vao, vbo, ebo, tex_vbo;
		static const unsigned int indices[54];

	private:
		glm::vec2 size = glm::vec2(0.f);
	};
}