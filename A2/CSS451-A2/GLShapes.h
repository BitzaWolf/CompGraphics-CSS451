#pragma once
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "SFML/System.hpp"

#include "SFGUI/SFGUI.hpp"
#include "SFGUI/Button.hpp"
#include "SFGUI/Window.hpp"
#include "SFGUI/Desktop.hpp"

class GLShapes
{
public:
	GLShapes();
	~GLShapes();

	void run();

	// Event functions
	void onButtonClick();

private:
	// SFGUI Elements
	sfg::SFGUI sfgui;
	sfg::Desktop desktop;
	sfg::Window::Ptr window;
	sfg::Button::Ptr button;

	// SFML Elements
	sf::RenderWindow* renderWindow;
	sf::Clock clock;

	// GL Shapes data
	std::vector<sf::Shape*> shapes;
};

