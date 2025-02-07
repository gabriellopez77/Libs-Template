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

		void setNormalizedTex(int posX, int posY, int width, int height);
		void setAnimatedSprite(int posX, int posY, int width, int height, int count, float delay, float dt);
		void setSlice();

		// definicoes do sprite
		static ml::Shader shader;
		ml::Slice* slice = nullptr;
		glm::vec2 position;
		glm::vec3 color;
		glm::vec2 size;
		float rotate = 0.f;
		float alpha = 1.f;
		float texCoords[8] = { 0 };

	protected:
		float animationDelayTime = 0.f;
		unsigned short animationStage = 0;

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