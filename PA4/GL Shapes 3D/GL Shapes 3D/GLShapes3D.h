#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"

#include "SFGUI/SFGUI.hpp"
#include "SFGUI/Button.hpp"
#include "SFGUI/Box.hpp"
#include "SFGUI/Desktop.hpp"
#include "SFGUI/Label.hpp"
#include "SFGUI/RadioButton.hpp"
#include "SFGUI/RadioButtonGroup.hpp"
#include "SFGUI/Scale.hpp"
#include "SFGUI/Window.hpp"

#include <vector>
#include <gl\GLU.h>

class GLShapes3D
{
public:
	GLShapes3D();
	~GLShapes3D();

	void run();

private:
	// SFGUI Elements
	sfg::SFGUI sfgui;
	sfg::Desktop desktop;
	sfg::Box::Ptr box;
	sfg::Window::Ptr window;
	sfg::RadioButtonGroup::Ptr radioButtGroup;
	sfg::Button::Ptr button_clear;
	sfg::RadioButton::Ptr radiobutt_Square;
	sfg::RadioButton::Ptr radiobutt_Circle;
	sfg::RadioButton::Ptr radiobutt_Triangle;
	sfg::Scale::Ptr slider_Red;
	sfg::Scale::Ptr slider_Green;
	sfg::Scale::Ptr slider_Blue;

	// SFML Elements
	sf::RenderWindow* renderWindow;
	sf::Clock clock;

	// GL Shapes data
	std::vector<sf::Shape*> shapes;

	// Event functions
	void onButtonClick();
	void onMouseClick(sf::Event &event);

	// Utility functions
	void deleteShapes();
};

