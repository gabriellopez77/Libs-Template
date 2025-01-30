#pragma once

#include "../glm/glm.hpp"

#include "Shader.h"
#include "Slice.h"

namespace ml {
	class Sprite {
	public:
		Sprite();

		virtual void draw();

		static void init(const char* texturePath);

		static glm::vec3 convertColor(unsigned char r, unsigned char g, unsigned char b) { return { r / 255.f, g / 255.f, b / 255.f }; }
		static int getVao() { return vao; }

		void setNormalizedTexUV(int posX, int posY, int width, int height);

		// definicoes do sprite
		static Shader* shader;
		glm::vec2 position;
		glm::vec3 color;
		glm::vec2 size;
		ml::Slice* slice = nullptr;
		float alpha = 1.f;
		float texCoords[8] = { 0 };

	protected:
		bool useTexture = false;

		static glm::mat4 model;

		static unsigned int vao;
		static unsigned int vbo;
		static unsigned int ebo;
		static unsigned int tex_vbo;
		static unsigned int textureID;

	private:
		static unsigned char* data;
	};
}