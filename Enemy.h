#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

//std
#include <iostream>
#include <time.h>
class Enemy
{
public:
	Enemy(float pos_x, float pos_y);
	~Enemy();

	void update();
	void render(sf::RenderTarget& target);

	const sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
	const sf::Vector2f& getPos() const { return shape.getPosition(); }
	const int getCurrHealth() const { return hp; }
	const int getHealthPool() const { return hpMax; }
	const int getDamage() const { return damage; }
	const int getPoints() const { return points; }
	void setHealth(int x) { hp += x; }

private:
	sf::CircleShape shape;
	size_t type, hp, hpMax, damage, points;
	float speed;

	sf::CircleShape initShape();


};

