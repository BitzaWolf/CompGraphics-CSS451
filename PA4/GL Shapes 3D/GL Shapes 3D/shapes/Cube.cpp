#include "Cube.h"

using namespace glshapes;

const float Cube::SIZE = 2.0f; // width and height of the cube.

Cube::Cube() { }

Cube::~Cube() { }

void Cube::draw() const
{
	float x1 = Shape::center.x - SIZE / 2;
	float x2 = x1 + SIZE;
	float y1 = Shape::center.y - SIZE / 2;
	float y2 = y1 + SIZE;
	float z1 = Shape::center.z - SIZE / 2;
	float z2 = z1 + SIZE;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(Shape::rotation.y, 0, 1, 0);
	glRotatef(Shape::rotation.x, 1, 0, 0);
	glRotatef(Shape::rotation.z, 0, 0, 1);
	glTranslatef(Shape::center.x, Shape::center.y, Shape::center.z);
	glBegin(GL_QUADS);

	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(x2, y2, z1);
	glVertex3f(x1, y2, z1);
	glVertex3f(x1, y2, z2);
	glVertex3f(x2, y2, z2);

	glColor3f(1.0f, 0.5f, 0.0f); // Orange
	glVertex3f(x2, y1, z2);
	glVertex3f(x1, y1, z2);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y1, z1);

	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(x2, y2, z2);
	glVertex3f(x1, y2, z2);
	glVertex3f(x1, y1, z2);
	glVertex3f(x2, y1, z2);

	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(x2, y1, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y2, z1);
	glVertex3f(x2, y2, z1);

	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(x1, y2, z2);
	glVertex3f(x1, y2, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1, z2);

	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(x2, y2, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x2, y1, z2);
	glVertex3f(x2, y1, z1);

	glEnd();
}
