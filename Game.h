#pragma once

#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
//std
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <sstream>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode vm;
	sf::Event event;
	sf::Font font;
	sf::Text UI_text;
	sf::Text GameOverText;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//background
	sf::Sprite WorldBG;
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpPoolBar;

	//game objects
	Player* player;
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	float spawnTimer;
	float spawnTimerMax;
	uint32_t score;
	

	void initWindow();
	void initTextures();
	void initGUI();

public:
	//ctor
	Game(sf::VideoMode rez);
	Game();

	Game(const Game& source) = delete;
	~Game();

	//Accessors

	void run();

	//methods
	void update();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateGUI();
	//generalized for any game object
	bool isCollision(const sf::FloatRect& obj1 ,const sf::FloatRect& obj2);

	void pollEvents();

	void render();
	void renderGUI();

};

