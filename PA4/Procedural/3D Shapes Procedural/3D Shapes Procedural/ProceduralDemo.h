#pragma once

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include <gl/GLU.h>

#include "ProceduralShape.h"

class ProceduralDemo
{
public:
	ProceduralDemo();
	~ProceduralDemo();

	void run();

private:
	//SFML Elements
	sf::RenderWindow* renderWindow;
	sf::Clock clock;

	// ProceduralDemo
	static const sf::Int32 TIME_BETWEEN_SHAPES; // in milliseconds
	static const float SPAWN_MOVE_SPEED; // in units per milliseconds

	std::vector<ProceduralShape*> shapes;
	sf::Int32 nextShapeTimer;
	sf::Vector3<float> spawnPosition;
	float tempFlipper;

	void drawPyramid();
};

