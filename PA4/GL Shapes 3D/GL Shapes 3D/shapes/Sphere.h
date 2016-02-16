/* Builds a 3D sphere object. */

#pragma once
#include "Shape.h"
#include <vector>

namespace glshapes
{
	class Sphere : public Shape
	{
	public:
		Sphere();
		~Sphere();

		void draw() const;

	private:
		std::vector<sf::Vector3f*> verticies;

		void drawFace(const int &v1, const int &v2, const int &v3, const sf::Vector3f &color) const;
	};
}

