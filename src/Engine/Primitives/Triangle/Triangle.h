#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../Primitive.h"

class Triangle : public Primitiv
{
private:
public:
	Triangle() : Primitiv()
	{
		Vertex vertices[]{
			//Position                       //Color                       //Texcoord             //Normal                        // Number
			vec3(-0.7f,   0.7f,  0.0f),      vec3(1.0f,  0.0f,  0.0f),     vec2(0.0f,  1.0f),     vec3(0.0f,  0.0f,  1.0f),      // 0
			vec3(-0.7f,  -0.7f,  0.0f),      vec3(0.0f,  1.0f,  0.0f),     vec2(0.0f,  0.0f),     vec3(0.0f,  0.0f,  1.0f),      // 1
			vec3(0.7f,   -0.7f,  0.0f),      vec3(0.0f,  0.0f,  1.0f),     vec2(1.0f,  0.0f),     vec3(0.0f,  0.0f,  1.0f),      // 2
		};
		GLuint countVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[]{
			//Vertex    // Number of polygon
			0, 1, 2,    // 1
		};
		GLuint countIndeces = sizeof(indices) / sizeof(GLuint);

		set(vertices, countVertices,
			indices, countIndeces);
	}
};

#endif
