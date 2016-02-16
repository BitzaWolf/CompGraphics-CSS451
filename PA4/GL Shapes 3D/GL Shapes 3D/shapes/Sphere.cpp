#include "Sphere.h"

using namespace glshapes;

Sphere::Sphere()
{
	// These vertices were generated using a 3D modeling program.
	verticies.push_back(new sf::Vector3f(0, -1.0f, 0));
	verticies.push_back(new sf::Vector3f(0.7236f, -0.447215f, 0.52572f));
	verticies.push_back(new sf::Vector3f(-0.276385f, -0.447215f, 0.85064f));

	verticies.push_back(new sf::Vector3f(-0.894425f, -0.447215f, 0));
	verticies.push_back(new sf::Vector3f(-0.276385f, -0.447215f, -0.85064f));
	verticies.push_back(new sf::Vector3f(0.7236f, -0.447215f, -0.52572f));

	verticies.push_back(new sf::Vector3f(0.276385f, 0.447215f, 0.85064f));
	verticies.push_back(new sf::Vector3f(-0.7236f, 0.447215f, 0.52572f));
	verticies.push_back(new sf::Vector3f(0.7236f, 0.447215f, -0.52572f));

	verticies.push_back(new sf::Vector3f(0.276385f, 0.447215f, -0.85064));
	verticies.push_back(new sf::Vector3f(0.894425f, 0.447215f, 0));
	verticies.push_back(new sf::Vector3f(0, 1.0f, 0));
}

Sphere::~Sphere()
{
	for (unsigned int i = 0; i < verticies.size(); ++i)
	{
		delete verticies.at(i);
	}
	verticies.empty();
}

void Sphere::draw()const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glTranslatef(center.x, center.y, center.z);
	glBegin(GL_TRIANGLES);

	// These face-building vertex orders were generated from a 3D modeling program.
	drawFace(1, 2, 3, sf::Vector3f(0.0f, 1.0f, 0.0f));
	drawFace(2, 1, 6, sf::Vector3f(1.0f, 0.5f, 0.0f));
	drawFace(1, 3, 4, sf::Vector3f(1.0f, 0.0f, 0.0f));

	drawFace(1, 4, 5, sf::Vector3f(1.0f, 1.0f, 0.0f));
	drawFace(1, 5, 6, sf::Vector3f(0.0f, 0.0f, 1.0f));
	drawFace(2, 6, 11, sf::Vector3f(1.0f, 0.0f, 1.0f));

	drawFace(3, 2, 7, sf::Vector3f(0.0f, 1.0f, 0.0f));
	drawFace(4, 3, 8, sf::Vector3f(1.0f, 0.5f, 0.0f));
	drawFace(5, 4, 9, sf::Vector3f(1.0f, 0.0f, 0.0f));

	drawFace(6, 5, 10, sf::Vector3f(1.0f, 1.0f, 0.0f));
	drawFace(2, 11, 7, sf::Vector3f(0.0f, 0.0f, 1.0f));
	drawFace(3, 7, 8, sf::Vector3f(1.0f, 0.0f, 1.0f));

	drawFace(4, 8, 9, sf::Vector3f(0.0f, 1.0f, 0.0f));
	drawFace(5, 9, 10, sf::Vector3f(1.0f, 0.5f, 0.0f));
	drawFace(6, 10, 11, sf::Vector3f(1.0f, 0.0f, 0.0f));

	drawFace(7, 11, 12, sf::Vector3f(1.0f, 1.0f, 0.0f));
	drawFace(8, 7, 12, sf::Vector3f(0.0f, 0.0f, 1.0f));
	drawFace(9, 8, 12, sf::Vector3f(1.0f, 0.0f, 1.0f));

	drawFace(10, 9, 12, sf::Vector3f(0.0f, 1.0f, 0.0f));
	drawFace(11, 10, 12, sf::Vector3f(1.0f, 0.5f, 0.0f));

	glEnd();
}

/*
*	Draw a single triangle (face) of the shape in the specified color.
*/
void Sphere::drawFace(const int &v1, const int &v2, const int &v3, const sf::Vector3f &color) const
{
	sf::Vector3f* vert1 = verticies.at(v1 - 1);
	sf::Vector3f* vert2 = verticies.at(v2 - 1);
	sf::Vector3f* vert3 = verticies.at(v3 - 1);

	glColor3f(color.x, color.y, color.z);
	glVertex3f(vert1->x, vert1->y, vert1->z);
	glVertex3f(vert2->x, vert2->y, vert2->z);
	glVertex3f(vert3->x, vert3->y, vert3->z);
}
