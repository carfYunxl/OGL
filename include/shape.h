#ifndef SHAPE_H
#define SHAPE_H
#include <shader/shader.h>
#include <texture.h>

class Shape {
public:
	virtual void draw() = 0;
	virtual ~Shape() {}
private:
	//Texture m_texture;
	//Shader m_shader;
};

class Triangle : public Shape {
public:
	Triangle(float* arr,Shader shad,Texture tex)
		:array(arr) ,
		m_shader(shad),
		m_texture(tex) {}
	virtual void draw() override {
		
	}

private:
	float* array;
	Shader m_shader;
	Texture m_texture;
};
#endif //SHAPE_H