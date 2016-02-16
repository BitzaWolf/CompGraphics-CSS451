/* Draws a 3D Cube. */
#pragma once
#include "Shape.h"

namespace glshapes
{
	class Cube : public Shape
	{
	public:
		Cube();
		virtual ~Cube();

		void draw() const;

	private:
		static const float SIZE;
		sf::Vector3<float> center;
		sf::Vector3f rotation;
	};
}
