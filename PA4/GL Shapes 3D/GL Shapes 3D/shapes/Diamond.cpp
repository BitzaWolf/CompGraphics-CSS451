#include "Diamond.h"

using namespace glshapes;

Diamond::Diamond()
{
	// These vertices were generated using a 3D modeling program.
	verticies.push_back(new sf::Vector3f(-1, -1, 1));
	verticies.push_back(new sf::Vector3f(-1, -1, -1));
	verticies.push_back(new sf::Vector3f(1, -1, -1));

	verticies.push_back(new sf::Vector3f(1, -1, 1));
	verticies.push_back(new sf::Vector3f(0, -3, -1));
	verticies.push_back(new sf::Vector3f(0, 1, 0));
}

Diamond::~Diamond()
{
	for (unsigned int i = 0; i < verticies.size(); ++i)
	{
		delete verticies.at(i);
	}
	verticies.empty();
}

void Diamond::draw()const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glTranslatef(center.x, center.y, center.z);
	glBegin(GL_TRIANGLES);

	drawFace(4, 6, 1, sf::Vector3f(0.0f, 1.0f, 0.0f));
	drawFace(3, 4, 5, sf::Vector3f(1.0f, 0.5f, 0.0f));
	drawFace(6, 2, 1, sf::Vector3f(1.0f, 0.0f, 0.0f));

	drawFace(6, 4, 3, sf::Vector3f(1.0f, 1.0f, 0.0f));
	drawFace(5, 1, 2, sf::Vector3f(0.0f, 0.0f, 1.0f));
	drawFace(3, 5, 2, sf::Vector3f(1.0f, 0.0f, 1.0f));

	drawFace(2, 6, 3, sf::Vector3f(0.0f, 1.0f, 0.0f));
	drawFace(5, 4, 1, sf::Vector3f(1.0f, 0.5f, 0.0f));

	glEnd();
}

/*
*	Draw a single triangle (face) of the shape in the specified color.
*/
void Diamond::drawFace(const int &v1, const int &v2, const int &v3, const sf::Vector3f &color) const
{
	sf::Vector3f* vert1 = verticies.at(v1 - 1);
	sf::Vector3f* vert2 = verticies.at(v2 - 1);
	sf::Vector3f* vert3 = verticies.at(v3 - 1);

	glColor3f(color.x, color.y, color.z);
	glVertex3f(vert1->x, vert1->y, vert1->z);
	glVertex3f(vert2->x, vert2->y, vert2->z);
	glVertex3f(vert3->x, vert3->y, vert3->z);
}
