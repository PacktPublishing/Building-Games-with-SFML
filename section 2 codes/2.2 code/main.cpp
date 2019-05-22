#include <SFML/Window.hpp>
#include <iostream>

int main()
{
	sf::Window window(sf::VideoMode::getFullscreenModes().front(), "Building Games with SFML", sf::Style::Fullscreen)
	
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
        //draw.here....
        window.display();
        
        window.setFramerateLimit(60);
        sf::sleep(sf::seconds(1.f/60.f);
    }
	 return EXIT_SUCCESS;
}

