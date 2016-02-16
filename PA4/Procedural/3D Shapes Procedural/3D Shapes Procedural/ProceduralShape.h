/*
Represents a square shape that will be drawn to the screen.
*/

#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"

class ProceduralShape
{
public:
	ProceduralShape();
	ProceduralShape(const sf::Vector3<float> &center);
	ProceduralShape(const float &x, const float &y, const float &z);
	~ProceduralShape();

	void update(const sf::Int32 &time);
	void draw() const;
	bool pastScreen() const;

private:
	static const float SIZE;  // distance from center to any side.
	static const float SPEED; // Units per millisecond to move this shape.

	sf::Vector3<float> center; // Center of this square in a 3D world
	sf::Vector3<float> direction; // Unit vector pointing from this square to the center of the screen.
};

