#include "Game.h"
#include <ctime>

//Private methods
void Game::initWindow()
{
    window = new sf::RenderWindow(vm, "Galaxica/Space Invaders Clone", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(90);
    window->setVerticalSyncEnabled(false);
}

void Game::initGUI()
{
    if (!font.loadFromFile("Fonts/DejaVuSans.ttf")) { std::cout << "File NOT FOUND\n"; }
    //score
    UI_text.setFont(font);
    UI_text.setCharacterSize(16);
    UI_text.setFillColor(sf::Color::White);
    UI_text.setPosition(vm.width - 100, 10);
    UI_text.setString("test");

    GameOverText.setFont(font);
    GameOverText.setCharacterSize(60);
    GameOverText.setFillColor(sf::Color::White);
    GameOverText.setPosition(window->getSize().x/3.f - GameOverText.getGlobalBounds().width / 2.5f, 
                    window->getSize().y / 2.45f - GameOverText.getGlobalBounds().height / 2.5f);
    GameOverText.setString("Game Over");
    //player healthbar    
    playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    playerHpBar.setFillColor(sf::Color::Red);
    playerHpBar.setOutlineColor(sf::Color(240, 50, 0, 255));
    playerHpBar.setOutlineThickness(2.f);
    playerHpBar.setPosition(20.f, 25.f);

    playerHpPoolBar.setSize(sf::Vector2f(playerHpBar.getSize().x + 10, playerHpBar.getSize().y + 5));
    playerHpPoolBar.setFillColor(sf::Color(30, 30, 30, 175));
    playerHpPoolBar.setPosition(15.f, 22.5f);
}

void Game::initTextures()
{
    textures["BULLET"] = sf::Texture();
    textures["BULLET"].loadFromFile("Textures/Bullet.png");
    textures["WORLDBG"] = sf::Texture();
    textures["WORLDBG"].loadFromFile("Textures/space.jpg");
}

Game::Game(sf::VideoMode rez)
    :window{ nullptr },
    vm{ rez },
    event{},
    player{ new Player() },
    spawnTimerMax{ 50.f },
    spawnTimer{ spawnTimerMax },
    score{ 0 }
{
    initWindow();
    initTextures();
    WorldBG.setTexture(textures["WORLDBG"]);
    WorldBG.setScale(.60f, .70f);
    initGUI();
}

Game::Game()
    : Game(sf::VideoMode(1000, 700, 32U)) {}

Game::~Game()
{
    delete player;
    for (auto& b : bullets) delete b;
    for (auto& e : enemies) delete e;
    delete window;
}

void Game::run()
{
    while (window->isOpen()) 
    {
        pollEvents();
        if (player->getHealth() > 0) 
        {  
            update();
            render();
        }
    }
}

void Game::update()
{
    updateGUI();
    player->update();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player->isAttack())
    {//left
        bullets.push_back(new Bullet(
            textures["BULLET"],
            player->getPos().x + player->getBounds().width / 3,//this makes bullet fire from center
            player->getPos().y,
            0.f,
            -1.f,
            10.f));
    }
    updateBullets();
    updateEnemies();
    updateCombat();
}

void Game::updateGUI()
{
    std::stringstream ss;
    ss << "Score: " << score;
    UI_text.setString(ss.str());

    float perc = static_cast<float>(player->getHealth()) / player->getHealthPool();
    playerHpBar.setSize(sf::Vector2f(perc * 300.f, 25.f));

    if (playerHpBar.getSize().x < 0)
    {
        playerHpBar.setFillColor(sf::Color::Transparent);
        playerHpBar.setOutlineColor(sf::Color::Transparent);
    }

}

void Game::updateBullets()
{
    int counter = 0;
    for (auto& b : bullets) 
    {
        b->update();
        if (b->getBounds().top + b->getBounds().height < 0.f) 
        {
            delete bullets.at(counter);
            bullets.erase(bullets.begin() + counter);
            counter--;
        }
        ++counter;
    }
}

void Game::updateEnemies()
{
    spawnTimer += .5f;
    if (spawnTimer >= spawnTimerMax)
    {
        enemies.push_back(new Enemy((rand() % 700)+20, (rand() % 50)-10));
        spawnTimer = 0.0f;
    }

    for (unsigned int i = 0; i < enemies.size(); i++) 
    {
        enemies[i]->update();
        if (isCollision(enemies[i]->getBounds(), player->getBounds()))
        {
            player->setHealth(-(enemies[i]->getDamage()));
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
        }
        else if (enemies[i]->getBounds().top > window->getSize().y)
        {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);   
        }
    }
}

void Game::updateCombat()
{
    for (unsigned int i = 0; i < enemies.size(); i++)
    {
        for (unsigned int j = 0; j < bullets.size(); j++)
        {
            if (isCollision(enemies[i]->getBounds(), bullets[j]->getBounds()))
            {
                enemies.at(i)->setHealth(-1);
                delete bullets.at(j);
                bullets.erase(bullets.begin() + j);

                if (enemies.at(i)->getCurrHealth() < 1) 
                {
                    score += enemies.at(i)->getPoints();
                    delete enemies.at(i);
                    enemies.erase(enemies.begin() + i);
                    break;
                }
                score++;
                
                break;
            }
        }
    }
}

bool Game::isCollision(const sf::FloatRect& obj1, const sf::FloatRect& obj2)
{
    //if(enemy.getBounds().intersects(bullet.getBounds())
    return obj1.intersects(obj2);
}

void Game::pollEvents()
{
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window->close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                window->close();
            break;
        }
    }
}

void Game::renderGUI()
{
    window->draw(UI_text);
    window->draw(playerHpPoolBar);
    window->draw(playerHpBar);
   
}

void Game::render()
{
    window->clear();
   
    window->draw(WorldBG);
    /*
     Draw game objects
    */
    player->render(*window);

    for (auto& e : enemies) e->render(*window);
    for (auto& b : bullets) b->render(*window);
    
    renderGUI();

    //GameOver 
    if (player->getHealth() < 1) {
        window->draw(GameOverText);
    }
    window->display();
}
