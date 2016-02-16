/*
Represents a 3D shape to be drawn by GLShapes3D.
This is an abstract class, subclasses must only implement the draw function.
*/
#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"

namespace glshapes
{
	class Shape
	{
	public:
		Shape();
		virtual ~Shape();

		virtual void translate(const float&, const float&, const float&);
		virtual void setPosition(const float &x, const float &y, const float &z);
		virtual void setRotation(const float &x, const float &y, const float &z);
		virtual void draw() const = 0;

	protected:
		sf::Vector3f center;
		sf::Vector3f rotation;
	};
}
