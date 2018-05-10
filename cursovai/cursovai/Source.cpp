#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <conio.h>

// E  -empty W- wall
enum  Block { O , X };

// класс, который хранит в себе положение курсора на оси рисовани€. 

class Point
{
private:
	int x;
	int y;

public:

	Point()
	{
		x = 0;
		y = 0;
	}
	Point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	void set_x(int _x)
	{
		x = _x;
	}
	void set_y(int _y)
	{
		y = _y;
	}
	int get_x()
	{
		return x;
	}
	int get_y()
	{
		return y;
	}
};

//в класс будем передавть   арту лабиринта,Ќачало —ќ   , ќкно, в котором нужно нарисовать,     ‘игуру, которую хотим нарисовать.


std::vector <sf::RectangleShape> wall_map;
sf::FloatRect rectangleBounds;
int static check_keyboard = 0;

 void print_map(int _size,
	 Block _block,
	 std::vector <std::vector<Block>> map,
	 std::vector <sf::RectangleShape> &wall_map,
	 Point _point,
	 sf::RenderWindow &_window,
	 sf::RectangleShape _rectangle,
	 int height){
	 
	for (int j(0); j < (map.size()); j++)
	{
		for (int i(0); i < (map.size()); i++)
		{
			if (map[j][i] == X)
			{
				_rectangle.setPosition(sf::Vector2f(_point.get_x(), _point.get_y()));
				_window.draw(_rectangle);
				_point.set_x(_point.get_x() + height);
			}
			if (map[j][i] == O)
			{
				_rectangle.setPosition(sf::Vector2f(_point.get_x(), _point.get_y()));
				_point.set_x(_point.get_x() + height);
			}
		}
		_point.set_x(0);
		_point.set_y(_point.get_y() + height);
	}
	_point.set_x(0);
	_point.set_y(0);

	static int check = 0;
	if (!check)
	{ 
	for (int j(0); j < (map.size()); j++)
	{
		for (int i(0); i < (map.size()); i++)
		{
			if (map[j][i] == X)
			{
				_rectangle.setPosition(sf::Vector2f(_point.get_x(), _point.get_y()));
				wall_map.push_back(_rectangle);
				_point.set_x(_point.get_x() + height);
			}
			if (map[j][i] == O)
			{
				_rectangle.setPosition(sf::Vector2f(_point.get_x(), _point.get_y()));
				_point.set_x(_point.get_x() + height);
			}
		}
		_point.set_x(0);
		_point.set_y(_point.get_y() + height);
	}
	_point.set_x(0);
	_point.set_y(0);
	check = 1;
	}

}



 void player_move(sf::Sprite &_sprite, sf::RectangleShape &_shadow, float &speed, int &player_position, float &time)
 {
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	 {
		 check_keyboard++;
	 }
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	 {
		 check_keyboard++;
	 }
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	 {
		 check_keyboard++;
	 }
	 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	 {
		 check_keyboard++;
	 }


	 if (check_keyboard == 1)
	 {
		 
	 float temp_speed = speed;
	 if (player_position == 0)
	 {
		 while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		 {  
			 speed = 0;
		 }
		 std::cout << time << std::endl;
		 speed = temp_speed;
		 _sprite.move(speed*time*5, 0);
		 _shadow.move(speed*time*5, 0);
	 }
	 if (player_position == 1)
	 {
		 while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		 {
			 speed = 0;
		 }
		 speed = 0;
		
		 speed = temp_speed;
		 _sprite.move(-speed * time, 0);
		 _shadow.move(-speed * time, 0);
	 }
	 if (player_position == 2)
	 {
		 while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		 {
			 speed = 0;
		 }
		 speed = 0;
		
		 speed = temp_speed;
		 _sprite.move(0, -speed * time);
		 _shadow.move(0, -speed * time);
	 }
	 if (player_position == 3)
	 {
		 while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		 {
			 speed = 0;
		 }
		 speed = 0;
		 speed = temp_speed;
		 _sprite.move(0, speed*time);
		 _shadow.move(0, speed*time);
	 }
	
	 }
	 check_keyboard = 0;
 }

 bool intersects(sf::FloatRect &shadowBounds, std::vector <sf::RectangleShape> &wall_map, bool &check_intersection)
 {

	 for (auto it : wall_map)
	 {
		 
	 
		 rectangleBounds = it.getGlobalBounds();

		 if (shadowBounds.intersects(rectangleBounds))
		 {
			 check_intersection = 1;
			 std::cout << "perecek" << std::endl;
		 }
		 else
		 {
			 check_intersection = 0;
			 std::cout << "neeeeee   perecek" << std::endl;
		 }
		 
	 }
	 return check_intersection;
 }

// передвижение персонажа по лабиринту
void moving(sf::Sprite &_sprite,
	sf::RectangleShape &_shadow,
	float  &_speed, float &_currentframe, float _time, int &pos, bool &intersection,
	sf::FloatRect &shadowBounds)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		check_keyboard++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		check_keyboard++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		check_keyboard++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		check_keyboard++;
	}

	if ((check_keyboard == 1)&&(!intersection))
	{
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		pos = 0;
		_currentframe += 0.005*_time;
		if (_currentframe > 4) _currentframe -= 4;
		_sprite.setTextureRect(sf::IntRect(int(_currentframe) * 64, 96, 64, 96));

		_sprite.move(-_speed * _time, 0);
		_shadow.move(-_speed * _time, 0);
	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{   
		pos = 1;
		_currentframe += 0.005*_time;
		if (_currentframe > 4) _currentframe -= 4;
		_sprite.setTextureRect(sf::IntRect(int(_currentframe) * 64, 192, 64, 96));

		_sprite.move(_speed*_time, 0);
		_shadow.move(_speed*_time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		pos = 2;
		_currentframe += 0.005*_time;
		if (_currentframe > 4) _currentframe -= 4;
		_sprite.setTextureRect(sf::IntRect(int(_currentframe) * 64, 0, 64, 96));

		_sprite.move(0, _speed*_time);
		_shadow.move(0, _speed*_time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		pos = 3;
		_currentframe += 0.005*_time;
		if (_currentframe > 4) _currentframe -= 4;
		_sprite.setTextureRect(sf::IntRect(int(_currentframe) * 64, 288, 64, 96));

		_sprite.move(0, -_speed * _time);
		_shadow.move(0, -_speed * _time);
	}
	
	  }
	check_keyboard = 0;
}




/*
std::vector <std::vector <sf::RectangleShape>> create_rectangle(int _size_rectangle, sf::RectangleShape _rectangle(sf::Vector2f()),std::vector <std::vector<Block>> map, std::vector <std::vector <sf::RectangleShape>> _wall_map){
	for (auto it : map)
	{
		int i = 0, j = 0;
		for (auto it_1 : it)
		{
			if (it_1 == 1)
			{
				_wall_map[i].push_back(_rectangle);
			}
			else
			{

			}
		}

	}
}

*/


int main()
{
	// image
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	
	Point point_1(0, 0);
	int  size = 20;
	int size_block = 30;
	Block block;

	float speed = 0.1;
    float time;

	int static player_position;


	sf::RenderWindow window(sf::VideoMode(1900, 920), "SFML Application");
	window.setFramerateLimit(60);//количество кадров в секунду

	// загрузка иконки персонажа
	image.loadFromFile("image.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(805, 50);
	sprite.setTextureRect(sf::IntRect(0, 0, 64, 96));

	//создание тени персонажа 
	sf::RectangleShape shadow;
	shadow.setSize(sf::Vector2f(16, 16));

	shadow.setPosition(805,50);
	shadow.move(24, 80);
	


	sf::RectangleShape rectangle(sf::Vector2f(size_block, size_block));

	//rectangle.setPosition(sf::Vector2f(0, 0));
	rectangle.setFillColor(sf::Color::Green);
	shadow.setFillColor(sf::Color::Blue);



	//std::vector <sf::RectangleShape> arr;
	std::vector <std::vector<Block>> map(size, std::vector<Block>(size, block));
	map[0] =  { X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,O,X,X,X };
	map[1] =  { X,O,O,O,O,O,O,X,O,O,O,X,O,O,X,O,O,O,O,X };
	map[2] =  { X,X,X,X,O,X,X,X,O,X,O,O,O,X,X,X,X,X,O,X };
	map[3] =  { X,O,O,X,O,X,O,X,X,X,O,X,X,X,O,O,X,O,O,X };
	map[4] =  { X,O,O,O,O,O,O,O,X,O,O,X,O,X,X,O,X,X,O,X };
	map[5] =  { X,O,X,X,X,X,X,O,O,O,O,X,O,X,O,O,O,O,O,X };
	map[6] =  { X,O,X,O,O,O,X,X,X,X,O,X,O,X,O,X,O,X,O,X };
	map[7] =  { X,O,X,X,X,O,O,O,X,O,O,X,O,O,O,X,O,X,X,X };
	map[8] =  { X,O,O,O,X,O,X,O,X,X,O,X,X,X,O,O,O,O,O,X };
	map[9] =  { X,X,X,O,X,O,X,O,X,O,O,O,O,X,O,X,X,X,O,X };
	map[10] = { X,O,X,O,O,O,X,X,X,O,X,X,X,X,O,X,O,O,O,X };
	map[11] = { X,O,O,O,X,O,X,O,X,O,X,O,O,O,O,X,O,X,O,X };
	map[12] = { X,O,X,X,X,O,O,O,O,O,X,O,X,X,X,X,O,X,O,X };
	map[13] = { X,O,O,X,O,O,X,X,X,O,O,O,X,O,X,O,O,X,O,X };
	map[14] = { X,X,O,X,X,O,X,O,X,O,X,X,X,O,X,X,O,X,X,X };
	map[15] = { X,O,O,O,O,O,O,O,X,O,O,O,O,O,O,X,O,O,O,X };
	map[16] = { X,O,X,O,X,X,X,O,O,O,X,O,O,X,O,X,X,X,O,X };
	map[17] = { X,O,X,O,O,O,X,X,X,X,X,O,X,X,O,O,O,X,O,X };
	map[18] = { X,O,O,O,X,O,O,O,O,O,O,O,X,O,O,X,O,O,O,X };
	map[19] = { X,X,X,X,X,O,X,X,X,X,X,X,X,X,X,X,X,X,X,X };


	//  создаем внутриигровой счетчик времени 
	static sf::Clock clock;

	

	float Currentframe = 0;
	
	sf::FloatRect shadowBounds;
	sf::FloatRect rectangleBounds;
	bool  check_intersection = 0;

	while (window.isOpen()) {

		//time
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();
		}

		shadowBounds = shadow.getGlobalBounds(); // get position player
		//sprite.setPosition(shadow.getGlobalBounds);
		//sprite.move(-2, -66);
		
		
		//bool intersects(sf::FloatRect &shadowBounds, std::vector <sf::RectangleShape> &wall_map, bool &check_intersection)
		

			for (auto it : wall_map)
			{

				if (shadowBounds.intersects(it.getGlobalBounds()))
				{
					
					check_intersection = 1;
					time = clock.getElapsedTime().asMicroseconds();
					clock.restart();
					time = time / 800;
					break;
				}
				else
				{
					check_intersection = 0;
				}
				
			}
			
			if (check_intersection == 1)
			{
				player_move(sprite, shadow, speed, player_position, time);
				clock.restart();
				time = clock.getElapsedTime().asMicroseconds();
				time = time / 800;
		}
			else
			{
				moving(sprite, shadow, speed, Currentframe, time, player_position, check_intersection, shadowBounds);
			}


		//intersects(shadowBounds, wall_map, check_intersection);
		
		
		
		


		window.clear();
		print_map(size, block, map, wall_map, point_1, window, rectangle, size_block);
		window.draw(sprite);
		window.draw(shadow);
		window.display();
	}
	return 0;
}

