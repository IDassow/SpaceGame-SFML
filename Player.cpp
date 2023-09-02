#include "Player.h"

sf::Sprite Player::init_sprite()
{
	sf::Sprite init;
	init.setTexture(texture);
	init.scale( 0.15f, 0.15f);

	return init;
}

sf::Texture Player::init_texture()
{
	sf::Texture init;
	if (!init.loadFromFile("Textures/PlayerShip.png")) {
		std::cout << "file failed \n";
	}
	return init;
}

//ctor
Player::Player()
	:texture{init_texture()}, 
	sprite{init_sprite()}
{
	sprite.setOrigin(sprite.getPosition().x / 2, sprite.getPosition().y / 2);
	sprite.setPosition(450.f, 500.f);
}

Player::~Player()
{
}

//methods
void Player::update()
{
	//MovePLayer
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {//left
		movement(-1.f, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {//right
		movement(1.f, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {//up
		movement(0, -1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {//down
		movement(0, 1.0f);
	}
	updateBounds();
	updateAttack();
}

const bool Player::isAttack()
{
	if (attackCoolDown >= attackcdMAX)
	{
		attackCoolDown = 0.f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (attackCoolDown < attackcdMAX) {
		attackCoolDown += 0.7f;
	}
}

void Player::updateBounds()
{

	if (getBounds().top < 400.f) {
		setPos(sf::Vector2f(getBounds().left, 400));
	}
	if (getBounds().top > 600.f) {
		setPos(sf::Vector2f(getBounds().left, 600));
	}
	if (getPos().x > 1000.f) {
		setPos(sf::Vector2f(-100.f, getBounds().top));
	}
	if (getPos().x < -100.f) {
		setPos(sf::Vector2f(1000.f, getBounds().top));
	}

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Player::movement(const float x, const float y)
{
	sprite.move(speed * x, speed * y);
}

const sf::Vector2f& Player::getPos() const
{
	return sprite.getPosition();
}

void Player::setPos(const sf::Vector2f pos)
{
	sprite.setPosition(pos.x, pos.y);
}

const sf::FloatRect Player::getBounds() const
{
	return sprite.getGlobalBounds();
}

void Player::setHealth(int x)
{
	health += x;
}


