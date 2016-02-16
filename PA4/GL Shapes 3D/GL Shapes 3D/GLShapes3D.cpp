#include "GLShapes3D.h"

using namespace sf;
using namespace sfg;

GLShapes3D::GLShapes3D()
{
	// Initialize graphical components.
	box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 20.0f);
	window = sfg::Window::Create();
	window->SetPosition(Vector2f(690, 0));
	window->SetTitle("ToolBox");
	renderWindow = new RenderWindow(VideoMode(800, 600), "GL shapes");

	// Create the GUI Controls
	box->Pack(sfg::Label::Create("X Position"));
	slider_x = Scale::Create(-20, 20, 0.1f);
	slider_x->SetValue(0);
	slider_x->GetSignal(Scale::OnMouseMove).Connect(std::bind(&GLShapes3D::transSlider, this));
	box->Pack(slider_x);

	box->Pack(sfg::Label::Create("Y Position"));
	slider_y = Scale::Create(-20, 20, 0.1f);
	slider_y->SetValue(0);
	slider_y->GetSignal(Scale::OnMouseMove).Connect(std::bind(&GLShapes3D::transSlider, this));
	box->Pack(slider_y);

	box->Pack(sfg::Label::Create("Z Position"));
	slider_z = Scale::Create(-100, -10, 0.2f);
	slider_z->SetValue(-10);
	slider_z->GetSignal(Scale::OnMouseMove).Connect(std::bind(&GLShapes3D::transSlider, this));
	box->Pack(slider_z);

	box->Pack(sfg::Label::Create("X Rotation"));
	slider_rotX = Scale::Create(0, 15, 0.2f);
	slider_rotX->SetValue(0);
	slider_rotX->GetSignal(Scale::OnMouseMove).Connect(std::bind(&GLShapes3D::rotSlider, this));
	box->Pack(slider_rotX);

	box->Pack(sfg::Label::Create("Y Rotation"));
	slider_rotY = Scale::Create(0, 15, 0.2f);
	slider_rotY->SetValue(0);
	slider_rotY->GetSignal(Scale::OnMouseMove).Connect(std::bind(&GLShapes3D::rotSlider, this));
	box->Pack(slider_rotY);

	box->Pack(sfg::Label::Create("Z Rotation"));
	slider_rotZ = Scale::Create(0, 360, 0.2f);
	slider_rotZ->SetValue(0);
	slider_rotZ->GetSignal(Scale::OnMouseMove).Connect(std::bind(&GLShapes3D::rotSlider, this));
	box->Pack(slider_rotZ);

	radioButtGroup = RadioButtonGroup::Create();
	radiobutt_Cube = RadioButton::Create("Cube", radioButtGroup);
	radiobutt_Cube->SetActive(true);
	box->Pack(radiobutt_Cube);

	radiobutt_Sphere = RadioButton::Create("Sphere", radioButtGroup);
	box->Pack(radiobutt_Sphere);

	radiobutt_Diamond = RadioButton::Create("Diamond", radioButtGroup);
	box->Pack(radiobutt_Diamond);

	button_clear = Button::Create("Clear Screen");
	button_clear->GetSignal(Button::OnLeftClick).Connect(std::bind(&GLShapes3D::onButtonClick, this));
	box->Pack(button_clear);

	window->Add(box);
	desktop.Add(window);
	// End creating GUI Controls.

	// Setup OpenGL
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 800 / 600.0f, 0.1f, 100.0f);

	// Setup GLShapes
	sf::RectangleShape rect(Vector2f(200, 200)); // Weird sfml initialization bug
	renderWindow->draw(rect);

	shapes.push_back(new glshapes::Cube()); // Draw a cube to the screen for now.
}

GLShapes3D::~GLShapes3D()
{
	delete renderWindow;
	deleteShapes();
}

void GLShapes3D::run()
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
			else if (event.type == Event::MouseButtonPressed)
			{
				onMouseClick(event);
			}
		}

		desktop.Update(elapsedTime.asSeconds()); // update GUI

		// There's a strange bug where the GUI library interferes with
		// OpenGL's gluPerspective function, so this has to be called
		// every render frame.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		gluPerspective(45.0f, 800 / 600.0f, 0.1f, 100.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		for (glshapes::Shape* shape : shapes) // draw all the Shapes
		{
			if (shape != NULL)
			{
				shape->draw();
			}
		}

		sfgui.Display(*renderWindow); // draw GUI
		renderWindow->display(); // Send the drawn data to the screen.

		sleep(milliseconds(8)); // Prevent the CPU from working needlessly hard.
	}
}

/* We only have 1 button, and its job is to clear the screen. */
void GLShapes3D::onButtonClick()
{
	deleteShapes();
}

/** onMouseClick
* This function is called from SFML's MouseClicked event. We want to draw
* a shape to the screen!
*/
void GLShapes3D::onMouseClick(Event &event)
{
	//We want to ignore mouse clicks over the GUI/Toolbar area, since the
	//user is trying to click a button, not draw over there.
	if (event.mouseButton.x >= 650)
	{
		return;
	}

	// We have the mouse click on the near plane, but the closest we place
	// objects in our 3D world is at z = -10.0
	// This means, we need to scale all components of the click location to
	// point to this new plane location.
	Vector3f planeCoordinates;
	planeCoordinates.x = (event.mouseButton.x - 400) / 8000.0f;
	planeCoordinates.y = (event.mouseButton.y - 300) / -6000.0f;
	planeCoordinates.z = -0.1; // distance from projector to near plane.

	planeCoordinates *= 100.0f; 

	glshapes::Shape *sp = NULL;

	// Determine which shape to draw.
	if (radiobutt_Cube->IsActive())
	{
		sp = new glshapes::Cube();
	}
	else if (radiobutt_Sphere->IsActive())
	{
		sp = new glshapes::Sphere();
	}
	else
	{
		sp = new glshapes::Diamond();
	}
	sp->setPosition(planeCoordinates.x, planeCoordinates.y, planeCoordinates.z);

	// Set the sliders to the values of this new shape.
	slider_x->SetValue(planeCoordinates.x);
	slider_y->SetValue(planeCoordinates.y);
	slider_z->SetValue(planeCoordinates.z);
	slider_rotX->SetValue(0);
	slider_rotY->SetValue(0);
	slider_rotZ->SetValue(0);

	// Save the shape so it's drawn later!
	shapes.push_back(sp);
}

/*
Represents all 3 of the translation sliders.
This function is called when the slider changes value.
*/
void GLShapes3D::transSlider()
{
	if (shapes.size() == 0)
	{
		return;
	}

	glshapes::Shape* s = shapes.back();
	float x = slider_x->GetValue();
	float y = slider_y->GetValue();
	float z = slider_z->GetValue();
	s->setPosition(x, y, z);
}

/*
Represents all 3 of the rotation sliders.
This function is called when the slider changes value.
*/
void GLShapes3D::rotSlider()
{
	if (shapes.size() == 0)
	{
		return;
	}

	glshapes::Shape* s = shapes.back();
	float x = slider_rotX->GetValue();
	float y = slider_rotY->GetValue();
	float z = slider_rotZ->GetValue();
	s->setRotation(x, y, z);
}

/* 
Deletes all of the shapes drawn to the screen, rendering the screen blank.
*/
void GLShapes3D::deleteShapes()
{
	for (glshapes::Shape* s : shapes)
	{
		if (s != NULL)
		{
			delete s;
		}
	}
	shapes.clear();
}
