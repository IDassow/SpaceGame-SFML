#include "Bullet.h"

Bullet::Bullet(sf::Texture& texture, float pos_x, float pos_y, float dir_x, float dir_y, float speed)
	:direction( dir_x,dir_y ), speed{ speed }
{
	shape.setTexture(texture);
	shape.setPosition(pos_x, pos_y);
	shape.setScale(0.1f, 0.1f);
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return shape.getGlobalBounds();
}

void Bullet::update()
{
	shape.move(speed * direction);
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
