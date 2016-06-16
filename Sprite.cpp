#include "Sprite.h"
#include "Vertex.h"


Sprite::Sprite()
{
	_vboID = 0;
}


Sprite::~Sprite()
{
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height){
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	
	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}

	Vertex vertrexData[3];

	vertrexData[0].position.x = x + width;
	vertrexData[0].position.y = y + height;

	vertrexData[1].position.x = x;
	vertrexData[1].position.y = y + height;

	vertrexData[2].position.x = x;
	vertrexData[2].position.y = y;

	for (int i = 0; i < 3; i++)
	{
		vertrexData[i].color.r = 255;
		vertrexData[i].color.g = 255;
		vertrexData[i].color.b = 255;
		vertrexData[i].color.a = 255;
	}
	

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertrexData), vertrexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0 ,0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
