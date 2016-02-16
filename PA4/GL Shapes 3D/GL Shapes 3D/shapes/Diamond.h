/* Builds a 3D diamond shape*/

#pragma once
#include "Shape.h"
#include <vector>

namespace glshapes
{
	class Diamond : public Shape
	{
	public:
		Diamond();
		~Diamond();

		void draw() const;

	private:
		static const float SIZE;
		std::vector<sf::Vector3f*> verticies;

		void drawFace(const int &v1, const int &v2, const int &v3, const sf::Vector3f &color) const;
	};
}

