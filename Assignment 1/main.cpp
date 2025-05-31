#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <stdexcept>

sf::Font load_font(const std::string& font_name)
{
	sf::Font my_Font;
	// attempt to load the font from a file
	if (!my_Font.loadFromFile(font_name))
	{
		throw std::runtime_error("Could not load font!\n");
	}
	else
		return my_Font;
}

struct Speed
{
	float x;
	float y;
};
struct Point_of_origin 
{
	float x;
	float y;
};



class Shape 
{
	sf::Text m_name;
	std::unique_ptr<sf::Shape> m_shape;
	Speed m_speed;
	Point_of_origin m_origin;
	
	
	
public:
	Shape(const sf::Font& font, const sf::Color& text_color,int text_size,
		const std::string& type,const std::string& name, 
		 float position_x,  float position_y, 
		 float speed_x,  float speed_y, 
		const sf::Color& color, float width, float height = 0)
		: m_name(name, font)
	{
		
		if (type == "Circle")
			m_shape = std::make_unique<sf::CircleShape>(width);
		else if (type == "Rectangle")
			m_shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
		else
			throw std::invalid_argument("Invalid shape type!\n");
		
		m_shape->setFillColor(color);
		m_speed = { speed_x, speed_y };
		m_origin.x = m_shape->getLocalBounds().getSize().x / 2.f;
		m_origin.y = m_shape->getLocalBounds().getSize().y / 2.f;
		m_shape->setOrigin(sf::Vector2f(m_origin.x, m_origin.y));
		m_shape->setPosition(sf::Vector2f(position_x, position_y));
;
		m_name.setFillColor(text_color);
		m_name.setCharacterSize(text_size);

		float num1 = (m_name.getLocalBounds().getPosition().x * 2 + m_name.getLocalBounds().getSize().x) / 2.f;
		float num2 = (m_name.getLocalBounds().getPosition().y * 2 + m_name.getLocalBounds().getSize().y) / 2.f;
		sf::Vector2f Center(num1, num2);
		m_name.setOrigin(Center);
	}


	 void draw(sf::RenderWindow &window) 
	{
		 float move;
		 float new_x = m_shape->getPosition().x + m_speed.x;
		 float new_y = m_shape->getPosition().y + m_speed.y;
		m_shape->setPosition(sf::Vector2f(new_x, new_y));
		m_name.setPosition(sf::Vector2f(new_x, new_y));
		if (m_shape->getPosition().x - m_origin.x < 0)
		{
			 move = 0;
			m_shape->setPosition(sf::Vector2f(move + m_origin.x, new_y));
			m_name.setPosition(sf::Vector2f(move + m_origin.x, new_y));
			m_speed.x *= -1; 
		}
		else if (m_shape->getPosition().x + m_origin.x > window.getSize().x)
		{
			move = window.getSize().x;
			m_shape->setPosition(sf::Vector2f(move - m_origin.x, new_y));
			m_name.setPosition(sf::Vector2f(move - m_origin.x, new_y));
			m_speed.x *= -1;
		}
		else if (m_shape->getPosition().y - m_origin.y < 0)
		{
			move = 0;
			m_shape->setPosition(sf::Vector2f(new_x , move + m_origin.y));
			m_name.setPosition(sf::Vector2f(new_x , move + m_origin.y));
			m_speed.y *= -1;
		}
		else if (m_shape->getPosition().y + m_origin.y > window.getSize().y)
		{
			move = window.getSize().y;
			m_shape->setPosition(sf::Vector2f(new_x, move - m_origin.y));
			m_name.setPosition(sf::Vector2f(new_x, move - m_origin.y));
			m_speed.y *= -1;
		}
		window.draw(*m_shape);
		window.draw(m_name);

	}


};


struct loaded
{
	
	int window_width=100, window_hight=100;
	std::vector<Shape> shapes;
	sf::Font font;  sf::Color font_color; int font_size=1;
	

	loaded(const std::string& file_name)
	{
		std::ifstream config(file_name);
		if (!config)
			throw std::runtime_error("Could not load config file!\n");
		std::string type;
		

		while (config >> type)
		{
			if (type == "Window")
			{
				config >> window_width;	config >> window_hight;
			}
			else if (type == "Font")
			{
				std::string name_font;
				config >> name_font;

				
				config >> font_size;
				std::cout << "font size: " << font_size << std::endl;
				int r, g, b;
				config >> r; config >> g; config >> b;
				font_color = sf::Color(r, g, b);
				font = load_font(name_font);

			}
			else if (type == "Circle" || type == "Rectangle")
			{
				std::string name;
				float position_x;	float position_y;
				float speed_x;		float speed_y;
				int color_r;		int color_g;		int color_b;
				float width;

				config >> name;
				config >> position_x; config >> position_y;
				config >> speed_x;		config >> speed_y;
				config >> color_r;		config >> color_g;		config >> color_b;
				config >> width;
				sf::Color shape_color(color_r, color_g, color_b);

				if (type == "Circle")
				{

					
					shapes.emplace_back(font, font_color, font_size, type, name, position_x, position_y, speed_x, speed_y, shape_color, width);
				}
				else if (type == "Rectangle")
				{
					float hight;

					config >> hight;

					shapes.emplace_back(font, font_color, font_size, type, name, position_x, position_y, speed_x, speed_y, shape_color, width, hight);
				}
			}
		}
	}
	
	

};


int main(int argc, char* argv[])
{

	loaded config("config.txt");

	sf::RenderWindow window(sf::VideoMode(config.window_width, config.window_hight), "ass 1");
	std::cout << config.window_width << " " << config.window_hight << std::endl;
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		try
		{
			// event handling
			sf::Event event;
			while (window.pollEvent(event))
			{
				// this event triggers when the window is closed
				if (event.type == sf::Event::Closed)

					window.close();



			}
			// basic animation - move the each frame if it's still in frame


			// basic rendering function calls
			window.clear();			// clear the window of anything previously drawn


			for (Shape& shape : config.shapes)
			{
				shape.draw(window);
			}
			window.display();		// call the window display function
		}
		catch (const std::exception& e) 
		{
			std::cerr << "Error: " << e.what() << std::endl;
			return 1;
		}
	}
	return 0;
}