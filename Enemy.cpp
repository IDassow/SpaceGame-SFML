#include "Enemy.h"

Enemy::Enemy(float pos_x, float pos_y)
	: shape{initShape()}, 
	hp{ shape.getPointCount()/2 }, 
	hpMax{ shape.getPointCount()/2 },  
	points{ shape.getPointCount() }, 
	speed{ 10.f }
{
	//hp, points, and speed dictated by shape vertices and shape size
	speed /= shape.getPointCount();
	shape.setPosition(pos_x, pos_y);
	damage = static_cast<int>(shape.getRadius()/10);
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
	shape.move(0.f, speed);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(shape);
}


sf::CircleShape Enemy::initShape()
{
	sf::CircleShape temp;
	temp.setRadius((rand() % 50) + 20);
	temp.setPointCount((rand() % 5) + 3);
	temp.setFillColor(sf::Color((rand()%255)+ 50, (rand() % 255) + 50, (rand() % 255) + 50, 255));
	temp.setOutlineColor(sf::Color(255, 100, 100, 100));
	temp.setOutlineThickness(3.f);
	return temp;
}
