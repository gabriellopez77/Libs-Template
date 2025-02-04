#include "Sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../glad/glad.h"
#include "../glm/gtc/matrix_transform.hpp"
#include "../stb/stb_image.h"

#include "MLGlobals.h"

#include <iostream>

ml::Shader ml::Sprite::shader(nullptr, nullptr);

unsigned int ml::Sprite::vao = 1;
unsigned int ml::Sprite::vbo = 1;
unsigned int ml::Sprite::ebo = 1;
unsigned int ml::Sprite::tex_vbo = 1;

unsigned char* ml::Sprite::data = nullptr;
unsigned int ml::Sprite::textureID = 0;

glm::mat4 ml::Sprite::model = glm::mat4(1.f);

ml::Sprite::Sprite() :
color(0.f),
position(0.f),
size(0.f)
{
}
void ml::Sprite::init(const char* texturePath) {
	ml::Slice::init();

	shader = Shader("dependencies/ml/shaders/sprite_vert.glsl", "dependencies/ml/shaders/sprite_frag.glsl");
	glUseProgram(shader.id);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &tex_vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), &VERTICES[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);


	// texture

	int nr;
	int x2;
	int y2;
	data = stbi_load(texturePath, &x2, &y2, &nr, 0);

	if (!data) {
		std::cout << "FALHA AO CARREGAR TEXTURA";
		return;
	}

	TEXTURE_SPRITES_SIZE.x = x2;
	TEXTURE_SPRITES_SIZE.y = y2;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	float color[]{ 1.f, 1.f, 1.f, 1.f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	// define o tipo de mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	// define o filtro da image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXTURE_SPRITES_SIZE.x, TEXTURE_SPRITES_SIZE.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// liberar a imagem da memoria
	stbi_image_free(data);
}

void ml::Sprite::draw() {
	bindShader(shader.id);
	bindTexture(textureID);

	if (slice) {
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(position, 0.f));
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.f, 0.f, 1.f));
		model = glm::scale(model, glm::vec3(1.f, 1.f, 0.f));
		glUniformMatrix4fv(shader.modelLoc, 1, GL_FALSE, &model[0][0]);

		bindVAO(slice->vao);

		glUniform1i(shader.useTextureLoc, true);

		// vertex
		glBindBuffer(GL_ARRAY_BUFFER, slice->vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(ml::quad), &slice->vertices[0]);

		// texture
		glBindBuffer(GL_ARRAY_BUFFER, slice->tex_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 9 * sizeof(ml::quad), &slice->tex[0]);

		glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, 0);
	}
	else {
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(position, 0.f));
		model = glm::rotate(model, 0.f, glm::vec3(0.f, 0.f, 1.f));

		model = glm::translate(model, glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.f));
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(size.x * -0.5f, size.y * -0.5f, 0.f));

		model = glm::scale(model, glm::vec3(size, 0.f));

		glUniformMatrix4fv(shader.modelLoc, 1, GL_FALSE, &model[0][0]);
		bindVAO(vao);

		if (useTexture) {
			glUniform1i(shader.useTextureLoc, true);
			glUniform1f(shader.alphaLoc, alpha);
			glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, texCoords);
		}
		else {
			glUniform1i(shader.useTextureLoc, false);
			glUniform1f(shader.alphaLoc, alpha);
			glUniform3fv(shader.colorLoc, 1, &color[0]);
		}

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void ml::Sprite::setSlice() {
	if (!slice)
		slice = new Slice(size.x, size.y);
}

void ml::Sprite::setNormalizedTex(int posX, int posY, int width, int height) {
	useTexture = true;

	// top right
	texCoords[0] = posX / TEXTURE_SPRITES_SIZE.x;
	texCoords[1] = posY / TEXTURE_SPRITES_SIZE.y;

	// bottom right
	texCoords[2] = posX / TEXTURE_SPRITES_SIZE.x;
	texCoords[3] = (posY + height) / TEXTURE_SPRITES_SIZE.y;

	// bottom left
	texCoords[4] = (posX + width) / TEXTURE_SPRITES_SIZE.x;
	texCoords[5] = (posY + height) / TEXTURE_SPRITES_SIZE.y;

	// top left
	texCoords[6] = (posX + width) / TEXTURE_SPRITES_SIZE.x;
	texCoords[7] = posY / TEXTURE_SPRITES_SIZE.y;
}