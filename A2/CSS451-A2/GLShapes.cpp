#include "GLShapes.h"

using namespace sf;
using namespace sfg;

GLShapes::GLShapes()
{
	button = Button::Create("Hello");
	button->GetSignal(Button::OnLeftClick).Connect(std::bind(&GLShapes::onButtonClick, this));

	window = sfg::Window::Create();
	window->SetTitle("GL Shapes - SFGUI Window");
	window->Add(button);

	desktop.Add(window);

	// SFML
	renderWindow = new RenderWindow(VideoMode(800, 600), "GL shapes");

	// GL Shapes
	
}


GLShapes::~GLShapes()
{
	delete renderWindow;
	// delete Shapes in the vector of shapes
}

void GLShapes::run()
{
	while (renderWindow->isOpen())
	{
		Time elapsedTime = clock.restart();

		Event event;
		while (renderWindow->pollEvent(event))
		{
			desktop.HandleEvent(event); // GUI event handler

			if (event.type == Event::Closed)
			{
				renderWindow->close();
			}
		}

		desktop.Update(elapsedTime.asSeconds()); // update GUI

		// Proof that I can access OpenGL directly.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (Shape* shape : shapes)
		{
			if (shape != NULL)
			{
				renderWindow->draw(*shape);
			}
		}

		sfgui.Display(*renderWindow); // draw GUI
		renderWindow->display();

		sleep(milliseconds(8));
	}
}

void GLShapes::onButtonClick()
{
	button->SetLabel("Wolf!");
}
