#include "Shape.h"

using namespace glshapes;

Shape::Shape()
{
	center.x = 0;
	center.y = 0;
	center.z = -10;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;
}

Shape::~Shape() { }

void Shape::translate(const float &dx, const float &dy, const float &dz)
{
	center.x += dx;
	center.y += dy;
	center.z += dz;
}

void Shape::setPosition(const float &x, const float &y, const float &z)
{
	center.x = x;
	center.y = y;
	center.z = z;
}

void Shape::setRotation(const float &x, const float &y, const float &z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}