#pragma once
//sfml
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
//std
#include <iostream>

class Bullet
{
public:
	Bullet(sf::Texture& texture, float pos_x, float pos_y, float dir_x, float dir_y, float speed);
	virtual ~Bullet();
	
	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget& target);
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float speed;
};

