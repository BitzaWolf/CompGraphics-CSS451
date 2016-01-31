// CSS451-A2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"

#include "SFGUI/SFGUI.hpp"
#include "SFGUI/Button.hpp"
#include "SFGUI/Window.hpp"
#include "SFGUI/Desktop.hpp"

using namespace sf;
using namespace sfg;

void onButtonClick();
Button::Ptr button;

int main()
{
	SFGUI sfgui; // initialize SFGUI

	CircleShape shape(100.0f);
	shape.setFillColor(Color::Green);

	// SFGUI
	button = Button::Create("Hello");
	button->GetSignal(Button::OnLeftClick).Connect(std::bind(&onButtonClick));
	
	auto window = sfg::Window::Create();
	window->SetTitle("GL Shapes - SFGUI Window");
	window->Add(button);

	sfg::Desktop desktop;
	desktop.Add(window);
	// end SFGUI

	RenderWindow renderWindow(VideoMode(800, 600), "GL shapes - SF RW");

	while (renderWindow.isOpen())
	{
		Event event;
		while (renderWindow.pollEvent(event))
		{
			desktop.HandleEvent(event); // GUI event handler

			if (event.type == Event::Closed)
			{
				renderWindow.close();
			}
		}

		desktop.Update(1.0f);

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		renderWindow.draw(shape);
		sfgui.Display(renderWindow);
		renderWindow.display();

		sleep(milliseconds(8));
	}
	return 0;
}

void onButtonClick()
{
	button->SetLabel("Wolf!");
}

