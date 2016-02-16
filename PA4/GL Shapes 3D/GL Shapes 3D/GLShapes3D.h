/*
This is the main demo class for the entire demonstration. Handles input,
GUI, and drawing the shapes to the screen.
*/
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

#include "shapes/Cube.h"
#include "shapes/Sphere.h"
#include "shapes/Diamond.h"

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
	sfg::RadioButton::Ptr radiobutt_Cube;
	sfg::RadioButton::Ptr radiobutt_Sphere;
	sfg::RadioButton::Ptr radiobutt_Diamond;
	sfg::Scale::Ptr slider_x;
	sfg::Scale::Ptr slider_y;
	sfg::Scale::Ptr slider_z;
	sfg::Scale::Ptr slider_rotX;
	sfg::Scale::Ptr slider_rotY;
	sfg::Scale::Ptr slider_rotZ;

	// SFML Elements
	sf::RenderWindow* renderWindow;
	sf::Clock clock;

	// GL Shapes data
	std::vector<glshapes::Shape*> shapes;

	// Event functions
	void onButtonClick();
	void onMouseClick(sf::Event &event);
	void transSlider();
	void rotSlider();

	// Utility functions
	void deleteShapes();
};

