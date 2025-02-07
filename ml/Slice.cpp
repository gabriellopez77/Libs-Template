#include "Slice.h"

#include "../glad/glad.h"

#include "MLGlobals.h"

#include <iostream>

unsigned int ml::Slice::vao = 0;
unsigned int ml::Slice::vbo = 0;
unsigned int ml::Slice::ebo = 0;
unsigned int ml::Slice::tex_vbo = 0;

const unsigned int ml::Slice::indices[54] = {
	0, 1, 3,	4, 5, 7,	8, 9,  11,
	1, 2, 3,    5, 6, 7,	9, 10, 11,

	12, 13, 15,		16, 17, 19,		20, 21, 23,
	13, 14, 15,		17, 18, 19,		21, 22, 23,

	24, 25, 27,		28, 29, 31,		32, 33, 35,
	25, 26, 27,		29, 30, 31,		33, 34, 35
};

ml::Slice::Slice(float x, float y) {
	size.x = x;
	size.y = y;
}

void ml::Slice::init() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &tex_vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(quad), NULL, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(quad), NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
}

void ml::Slice::setNormalizedTex(int posX, int posY, int width, int height, int corner) {
	boardSize = corner * 3.f;
	setVertexSize(size.x, size.y);

	float cx = corner / TEXTURE_SPRITES_SIZE.x;
	float cy = corner / TEXTURE_SPRITES_SIZE.y;

	float left = posX / TEXTURE_SPRITES_SIZE.x;
	float right = (posX + width) / TEXTURE_SPRITES_SIZE.x;
	float top = posY / TEXTURE_SPRITES_SIZE.y;
	float bottom = (posY + height) / TEXTURE_SPRITES_SIZE.y;

	//		   TR						   BR						   BL						   TL
	tex[0] = { {left,		 top	    }, {left,		 top    + cy}, {left   + cx, top	+ cy}, {left   + cx, top	    } };
	tex[1] = { {left   + cx, top		}, {left   + cx, top    + cy}, {right  - cx, top	+ cy}, {right  - cx, top	    } };
	tex[2] = { {right  - cx, top		}, {right  - cx, top    + cy}, {right,	     top	+ cy}, {right,		 top	    } };

	tex[3] = { {left,		 top    + cy}, {left,		 bottom - cy}, {left   + cx, bottom - cy}, {left   + cx, top    + cy} };
	tex[4] = { {left   + cx, top    + cy}, {left   + cx, bottom - cy}, {right  - cx, bottom - cy}, {right  - cx, top    + cy} };
	tex[5] = { {right  - cx, top    + cy}, {right  - cx, bottom - cy}, {right,		 bottom - cy}, {right,		 top    + cy} };

	tex[6] = { {left,		 bottom - cy}, {left,		 bottom		}, {left   + cx, bottom     }, {left   + cx, bottom - cy} };
	tex[7] = { {left   + cx, bottom - cy}, {left   + cx, bottom		}, {right  - cx, bottom		}, {right  - cx, bottom - cy} };
	tex[8] = { {right  - cx, bottom - cy}, {right  - cx, bottom		}, {right,		 bottom     }, {right,		 bottom - cy} };
}

void ml::Slice::setVertexSize(float sizeX, float sizeY) {
	float x1 = 0.f;
	float x2 = boardSize;
	float x3 = sizeX - boardSize;
	float x4 = sizeX;

	float y1 = 0.f;
	float y2 = boardSize;
	float y3 = sizeY - boardSize;
	float y4 = sizeY;

	vertices[8] = { {x3, y3}, {x3, y4}, {x4, y4}, {x4, y3} }; // 1
	vertices[7] = { {x2, y3}, {x2, y4}, {x3, y4}, {x3, y3} }; // 2
	vertices[6] = { {x1, y3}, {x1, y4}, {x2, y4}, {x2, y3} }; // 3

	vertices[5] = { {x3, y2}, {x3, y3}, {x4, y3}, {x4, y2} }; // 4
	vertices[4] = { {x2, y2}, {x2, y3}, {x3, y3}, {x3, y2} }; // 5
	vertices[3] = { {x1, y2}, {x1, y3}, {x2, y3}, {x2, y2} }; // 6

	vertices[2] = { {x3, y1}, {x3, y2}, {x4, y2}, {x4, y1} }; // 7
	vertices[1] = { {x2, y1}, {x2, y2}, {x3, y2}, {x3, y1} }; // 8
	vertices[0] = { {x1, y1}, {x1, y2}, {x2, y2}, {x2, y1} }; // 9
}