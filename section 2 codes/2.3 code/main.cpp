#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Building Games with SFML");
	
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(200, 100));
	rectangle.setFillcolor(sf::Color::Green);
	
	sf::CircleShape circle;
	circle.radius(20);
	circle.setFillColor(sf::Color::Blue);
	circle.setOutlineThickness(4);
	circle.setOutlineColor(sf::Color::Yellow);
	
	sf::ConvexShape customShape;
	customShape.setPointCount(3);
	customShape.setPoint(0, sf::Vector2f(0,0));
	customShape.setPoint(1, sf::Vector2f(150,30));
	customShape.setPoint(2, sf::Vector2f(0,60));
	
	customShape.setFillColor(sf::Color::Magenta);
	
	sf::Image image;
	image.loadFromFile("assets/image.png");
	
	sf::Texture texture;
	texture.loadFromImage(image);
	
	sf::Sprite sprite(texture);
	
	sf::Font font;
	font.loadFromFile("font.ttf");
	
	
	sf::Text text;
	text.setFont(font);
	text.setString("ola SFML");
	text.setColor(sf::Color::Red);
	
	
	sf::Sprite sprite2(texture);
	sprite2.setPosition(300, 300);
	sprite2.setRotation(45);
	
	rectangle.setPosition(10, 10);
	circle.setPosition(400, 50);
	customShape.setPosition(250, 250);
	
	 while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			
            if (event.type == sf::Event::Closed)
                window.close();   
                     
                     if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                     window.close();
                     {						
					 }
					 
					 if (event.mouseButton.button == sf::Mouse::Left)
					 std::cout << "Left Button";
					 
					 else if (event.mouseButton.button == sf::Mouse::Right)
					 std::cout << "Right Button";
					 std::cout << event.mouseButton.x << "&" << event.mouseButton.y << std::endl;
					   
        }
        
        window.clear();
        
        window.draw(rectangle);
        window.draw(circle);
        window.draw(customShape);
        window.draw(sprite);
        window.draw(sprite2);
        window.draw(text);
        
        window.display();
        
        window.setFramerateLimit(60);
        sf::sleep(sf::seconds(1.f/60.f);
    }
	 return EXIT_SUCCESS;
}


