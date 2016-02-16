#include "ProceduralShape.h"

const float ProceduralShape::SIZE = 2.0f; 
const float ProceduralShape::SPEED = 20.0f / 1000; // units per millisecond

ProceduralShape::ProceduralShape()
{
	center.x = 0;
	center.y = 0;
	center.z = -50.0f;

	direction.x = 0;
	direction.y = 0;
	direction.z = 1.0f;
}

ProceduralShape::ProceduralShape(const sf::Vector3<float> &center)
{
	this->center = center;

	direction.x = -center.x;
	direction.y = -center.y;
	direction.z = -center.z;
	
	float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
	direction /= length;
}

ProceduralShape::ProceduralShape(const float &x, const float &y, const float &z)
{
	center.x = x;
	center.y = y;
	center.z = z;

	direction.x = -center.x;
	direction.y = -center.y;
	direction.z = -center.z;

	float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));
	direction /= length;
}

ProceduralShape::~ProceduralShape() { }

/*
Move this square closer to the screen at a fixed speed based on the time
elapsed since this function was last called. This should be called every
frame.
*/
void ProceduralShape::update(const sf::Int32 &time)
{
	float zTranslation = SPEED * time;
	float scalar = zTranslation / direction.z;

	sf::Vector3<float> translation = scalar * direction;
	center += translation;
}

void ProceduralShape::draw() const
{
	glBegin(GL_QUADS);

	float x1 = center.x - SIZE / 2;
	float x2 = x1 + SIZE;
	float y1 = center.y - SIZE / 2;
	float y2 = y1 + SIZE;

	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(x1, y1, center.z);
	glVertex3f(x2, y1, center.z);
	glVertex3f(x2, y2, center.z);
	glVertex3f(x1, y2, center.z);

	glEnd();
}

/* Returns true if this square is behind the near clipping plane.*/
bool ProceduralShape::pastScreen() const
{
	return (center.z >= 0);
}
