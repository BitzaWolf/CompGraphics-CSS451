#include "ProceduralDemo.h"

using namespace sf;

const Int32 ProceduralDemo::TIME_BETWEEN_SHAPES = 100;
const float ProceduralDemo::SPAWN_MOVE_SPEED = 5.0f / 1000;

ProceduralDemo::ProceduralDemo()
{
	renderWindow = new RenderWindow(VideoMode(800, 600), "3D Procedural Demo");

	// initialize OpenGL States
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearColor(0, 0, 0, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 800 / 600.0f, 0.1f, 100.0f);

	// Procedural Demo
	srand(static_cast <unsigned> (time(0)));
	nextShapeTimer = TIME_BETWEEN_SHAPES;
	spawnPosition.x = 0;
	spawnPosition.y = 0;
	spawnPosition.z = -50;
	theta = 0;
}


ProceduralDemo::~ProceduralDemo()
{
	delete renderWindow;
	for (ProceduralShape* shape : shapes)
	{
		if (shape != NULL)
		{
			delete shape;
		}
	}
}

void ProceduralDemo::run()
{
	while (renderWindow->isOpen())
	{
		Time elapsedTime = clock.restart();
		Event event;

		while (renderWindow->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				renderWindow->close();
			}
		}

		// update spawn position
		theta += (90 / 2000.0f) * elapsedTime.asMilliseconds();
		spawnPosition.y = sin(theta * 3.14159265 / 180) * 5;
		spawnPosition.x = cos(theta * 3.14159265 / 180) * 7;

		nextShapeTimer -= elapsedTime.asMilliseconds();
		if (nextShapeTimer <= 0)
		{
			shapes.push_back(new ProceduralShape(spawnPosition));
			nextShapeTimer += TIME_BETWEEN_SHAPES;
		}

		// Draw shapes
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		for (ProceduralShape* shape : shapes)
		{
			if (shape != NULL)
			{
				shape->update(elapsedTime.asMilliseconds());
				shape->draw();
			}
		}

		for (int i = 0; i < shapes.size(); ++i)
		{
			ProceduralShape *shape = shapes.at(i);
			if (shape != NULL && shape->pastScreen())
			{
				delete shape;
				shapes.erase(shapes.begin() + i);
			}
		}

		renderWindow->display();
		sleep(milliseconds(8));
	}
}
