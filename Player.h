#pragma once
//sfml
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

//std
#include <iostream>

class Player
{
public:
	//ctor
	Player();
	~Player();

	//methods
	void update();
	void updateAttack();
	void updateBounds();
	void render(sf::RenderTarget& target);
	
	void movement(const float x, const float y);
	const sf::Vector2f& getPos() const;
	void setPos(const sf::Vector2f pos);
	const sf::FloatRect getBounds() const;
	const int& getHealth() const { return health; }
	const int& getHealthPool() const { return healthPool; }
	void setHealth(int x);
	const bool isAttack();

private:

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Sprite init_sprite();
	sf::Texture init_texture();
	int healthPool{ 10 };
	int health{ healthPool };
	float attackcdMAX{ 10.f }, attackCoolDown{ attackcdMAX }, speed{ 5.f };

};

