#include "GLShapes.h"

using namespace sf;
using namespace sfg;

/** Creates a new GLShapes application, all set to be run.
* Call the method run() to start the application.
*/
GLShapes::GLShapes()
{
	box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 20.0f);
	window = sfg::Window::Create();
	window->SetPosition(Vector2f(690, 0));
	window->SetTitle("ToolBox");
	renderWindow = new RenderWindow(VideoMode(800, 600), "GL shapes");

	// Create the GUI Controls
	box->Pack(sfg::Label::Create("Red"));
	slider_Red = Scale::Create(0, 255, 1);
	slider_Red->SetValue(255);
	box->Pack(slider_Red);

	box->Pack(sfg::Label::Create("Green"));
	slider_Green = Scale::Create(0, 255, 1);
	slider_Green->SetValue(255);
	box->Pack(slider_Green);

	box->Pack(sfg::Label::Create("Blue"));
	slider_Blue = Scale::Create(0, 255, 1);
	slider_Blue->SetValue(255);
	box->Pack(slider_Blue);

	radioButtGroup = RadioButtonGroup::Create();
	radiobutt_Square = RadioButton::Create("Square", radioButtGroup);
	radiobutt_Square->SetActive(true);
	box->Pack(radiobutt_Square);

	radiobutt_Circle = RadioButton::Create("Circle", radioButtGroup);
	box->Pack(radiobutt_Circle);

	radiobutt_Triangle = RadioButton::Create("Triangle", radioButtGroup);
	box->Pack(radiobutt_Triangle);

	button_clear = Button::Create("Clear Screen");
	button_clear->GetSignal(Button::OnLeftClick).Connect(std::bind(&GLShapes::onButtonClick, this));
	box->Pack(button_clear);

	window->Add(box);
	desktop.Add(window);


	// GL Shapes
	Shape* sp = new CircleShape(50.0f);
	sp->setFillColor(Color::Yellow);
	sp->setPosition(Vector2f(50, 50));
	shapes.push_back(sp);

	sp = new RectangleShape(Vector2f(80, 40));
	sp->setFillColor(Color::Green);
	sp->setPosition(Vector2f(250, 400));
	shapes.push_back(sp);
}


GLShapes::~GLShapes()
{
	delete renderWindow;
	deleteShapes();
}

/** run
* This is the main function for GLShapes. It contains a loop that occupies the
* calling thread until the sf::RenderWindow is closed.
* 
* There are 3 main parts to the loop:
* 1) Get time passed.
* 2) Check for Events and respond to them.
* 3) Draw
*/
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
			else if (event.type == Event::MouseButtonPressed)
			{
				onMouseClick(event);
			}
		}

		desktop.Update(elapsedTime.asSeconds()); // update GUI

		// Proof that I can access OpenGL directly.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (Shape* shape : shapes) // draw all the Shapes
		{
			if (shape != NULL)
			{
				renderWindow->draw(*shape);
			}
		}

		sfgui.Display(*renderWindow); // draw GUI
		renderWindow->display(); // Send the drawn data to the screen.

		sleep(milliseconds(8)); // Prevent the CPU from working needlessly hard.
	}
}

/** onButtonClick
* This function is called only from SFGUI's button, so we know it must be
* the clear-screen button.
*/
void GLShapes::onButtonClick()
{
	deleteShapes();
}

/** onMouseClick
* This function is called from SFML's MouseClicked event. We want to draw
* a shape to the screen!
*/
void GLShapes::onMouseClick(Event &event)
{
	Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
	Vector2f shapeCenter = mousePos - Vector2f(20, 20);
	
	// We want to ignore mouse clicks over the GUI/Toolbar area, since the
	// user is trying to click a button, not draw over there.
	if (mousePos.x < 650)
	{
		Shape *sp;
		
		// Determine which shape to draw.
		if (radiobutt_Square->IsActive())
		{
			sp = new RectangleShape(Vector2f(40, 40));
			sp->setPosition(shapeCenter);
		}
		else if (radiobutt_Circle->IsActive())
		{
			sp = new CircleShape(20);
			sp->setPosition(shapeCenter);
		}
		else
		{
			ConvexShape* shape = new ConvexShape(3);
			shape->setPoint(0, Vector2f(20, 0));
			shape->setPoint(1, Vector2f(0, 40));
			shape->setPoint(2, Vector2f(40, 40));
			sp = shape;
			sp->setPosition(shapeCenter);
		}

		// Calculate the color;
		sf::Color color;
		color.r = slider_Red->GetValue();
		color.g = slider_Green->GetValue();
		color.b = slider_Blue->GetValue();
		sp->setFillColor(color);

		// Save the shape so it's drawn later!
		shapes.push_back(sp);
	}
}

/** deleteShapes
* Deletes all of the shapes drawn to the screen, rendering the screen blank.
*/
void GLShapes::deleteShapes()
{
	for (Shape* s : shapes)
	{
		if (s != NULL)
		{
			delete s;
		}
	}
	shapes.clear();
}
