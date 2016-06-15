#pragma once

struct Vertex
{
	struct Position
	{
		float x;
		float y;
	} position;

	struct Color
	{
		unsigned int r;
		unsigned int g;
		unsigned int b;
		unsigned int a;
	} color;
};