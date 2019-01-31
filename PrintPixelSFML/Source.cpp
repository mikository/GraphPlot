#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using sf::RenderWindow;
using sf::RectangleShape;
using std::vector;
using sf::Vector2;
using sf::Color;
using sf::VideoMode;
using sf::Event;
using std::cout;
using std::cin;

const int WINDOW_WIDTH = 1000;
const int AXIS_SIZE = 800;
const int WINDOW_HEIGHT = 800;


//Method to create a rectangle colored, positioned and with fixed size of 1px
RectangleShape addPixel(sf::Vector2f position, sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue);
void drawLinearGraph(float a, float b, vector<RectangleShape> &pixels);
void drawLineYOnTheRight(vector<RectangleShape> &pixels);
void drawAxis(vector<RectangleShape> &pixels);
void revertGraphY(vector <RectangleShape> &graph, bool revert);
void addToAxis(vector <RectangleShape> &addPixels, vector<RectangleShape> &pixels);
void defineWindow(RenderWindow &window, char* name, Color color);

int main() {

	cout << "Enter a and b" << std::endl;
	float a, b;
	cin >> a >> b;

	//Create a window
	RenderWindow window;
	defineWindow(window, "Graph", Color::White);

	vector<RectangleShape> pixels;

	drawAxis(pixels);
	drawLineYOnTheRight(pixels);
	drawLinearGraph(a, b, pixels);
	


	//Iterate through the pixel vector
	for (const auto& pixel : pixels)
	{
		//Draw each pixel
		window.draw(pixel);
	}
	//Display/Update window
	window.display();

	//Check if window is open 
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
		}
	}

}
RectangleShape addPixel(sf::Vector2f position, sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue)
{
	sf::RectangleShape pixel;
	pixel.setSize({ 2.f, 2.f });
	pixel.setFillColor({ red, green, blue });
	pixel.setPosition(position);
	return pixel;
}
void drawLinearGraph(float a, float b, vector<RectangleShape> &pixels) {
	vector<RectangleShape> graph;
	//Draw some lines ;)
	float finalY = 0;
	
	for (float x =  -1 * AXIS_SIZE / 2 + 10, y = 0; y < AXIS_SIZE/2 - 10  && x < AXIS_SIZE/2 - 10; x ++) {
		y = x * abs(a) + b;
		finalY = y;
		cout << x << " " << y << std::endl;
		graph.push_back(addPixel({ x,  y }, 0, 0, 255));
	}
	revertGraphY(graph, a > 0);
	addToAxis(graph, pixels);
	cout << finalY;
}
void drawAxis(vector<RectangleShape> &pixels) {
	//Draw axis
	for (float i = 10; i < AXIS_SIZE - 10; i+=2) {
		//x
		pixels.push_back(addPixel({ i , AXIS_SIZE / 2 }, 0, 255, 0));
		//y
		pixels.push_back(addPixel({ AXIS_SIZE / 2, i }, 255, 0, 0));
	}
}
void revertGraphY(vector <RectangleShape> &graph, bool revert = true)
{
	for (RectangleShape& pixel : graph)
	{
		//Draw each pixel
		float x = pixel.getPosition().x + AXIS_SIZE / 2;
		float y = !revert? (pixel.getPosition().y + AXIS_SIZE / 2):AXIS_SIZE - (pixel.getPosition().y + AXIS_SIZE / 2);
		
		pixel.setPosition(x, y);
	}
}
void addToAxis(vector <RectangleShape> &addPixels, vector<RectangleShape> &pixels)
{
	for (const RectangleShape &p : addPixels) {
		pixels.push_back(p);
	}
}
void defineWindow(RenderWindow &window, char* name, Color color)
{
	window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), name);
	window.setFramerateLimit(60);
	window.clear(color);

}
void drawLineYOnTheRight(vector<RectangleShape> &pixels) 
{
	for (int i = 0; i < WINDOW_HEIGHT; i++)
	{
		pixels.push_back(addPixel({ (float)AXIS_SIZE, (float)i }, 0, 0, 0));
	}
}