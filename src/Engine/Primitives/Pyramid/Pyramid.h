#ifndef PYRAMID_H
#define PYRAMID_H

#include "../Primitive.h"

class Pyramid : public Primitiv
{
private:
public:
	Pyramid() : Primitiv()
	{
		Vertex vertices[]{
			//Position                    //Color                    //Texcoord          //Normal                      // Number
			vec3(+0.0f,  +0.5f,  +0.0f),  vec3(1.0f,  1.0f,  1.0f),  vec2(0.5f,  1.0f),  vec3(+0.0f,  +0.0f,  +1.0f),   // 0
			vec3(-0.5f,  -0.5f,  +0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(0.0f,  0.0f),  vec3(+0.0f,  +0.0f,  +1.0f),   // 1
			vec3(+0.5f,  -0.5f,  +0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(1.0f,  0.0f),  vec3(+0.0f,  +0.0f,  +1.0f),   // 2

			vec3(+0.0f,  +0.5f,  +0.0f),  vec3(1.0f,  1.0f,  1.0f),  vec2(0.5f,  1.0f),  vec3(-1.0f,  +0.0f,  +0.0f),   // 3
			vec3(-0.5f,  -0.5f,  -0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(0.0f,  0.0f),  vec3(-1.0f,  +0.0f,  +0.0f),   // 4
			vec3(-0.5f,  -0.5f,  +0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(1.0f,  0.0f),  vec3(-1.0f,  +0.0f,  +0.0f),   // 5

			vec3(+0.0f,  +0.5f,  +0.0f),  vec3(1.0f,  1.0f,  1.0f),  vec2(0.5f,  1.0f),  vec3(+0.0f,  +0.0f,  -1.0f),   // 6
			vec3(+0.5f,  -0.5f,  -0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(0.0f,  0.0f),  vec3(+0.0f,  +0.0f,  -1.0f),   // 7
			vec3(-0.5f,  -0.5f,  -0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(1.0f,  0.0f),  vec3(+0.0f,  +0.0f,  -1.0f),   // 8

			vec3(+0.0f,  +0.5f,  +0.0f),  vec3(1.0f,  1.0f,  1.0f),  vec2(0.5f,  1.0f),  vec3(+1.0f,  +0.0f,  -1.0f),   // 9
			vec3(+0.5f,  -0.5f,  +0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(0.0f,  0.0f),  vec3(+1.0f,  +0.0f,  -1.0f),   // 10
			vec3(+0.5f,  -0.5f,  -0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(1.0f,  0.0f),  vec3(+1.0f,  +0.0f,  -1.0f),   // 11
			
			vec3(+0.5f,  -0.5f,  +0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(1.0f,  1.0f),  vec3(+0.0f,  -1.0f,  +0.0f),   // 12
			vec3(-0.5f,  -0.5f,  -0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(0.0f,  0.0f),  vec3(+0.0f,  -1.0f,  +0.0f),   // 13
			vec3(+0.5f,  -0.5f,  -0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(1.0f,  0.0f),  vec3(+0.0f,  -1.0f,  +0.0f),   // 14
			
			vec3(-0.5f,  -0.5f,  +0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(0.0f,  1.0f),  vec3(+0.0f,  -1.0f,  +0.0f),   // 15
			vec3(-0.5f,  -0.5f,  -0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(0.0f,  0.0f),  vec3(+0.0f,  -1.0f,  +0.0f),   // 16
			vec3(+0.5f,  -0.5f,  +0.5f),  vec3(1.0f,  1.0f,  1.0f),  vec2(1.0f,  1.0f),  vec3(+0.0f,  -1.0f,  +0.0f),   // 13
			

		};
		GLuint countVertices = sizeof(vertices) / sizeof(Vertex);

		set(vertices, countVertices, nullptr, 0);
	}
};

#endif
