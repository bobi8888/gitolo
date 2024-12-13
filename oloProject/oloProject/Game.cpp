#include "Game.h"

//static methods

//Initializer methods

//Constructors/Destructions

void Game::initWindow()
{
	//for gameplay
	// sf::RenderWindow window(sf::VideoMode(900, 900), "olo", sf::Style::None);
	// 
	//for testing
	this->window = new sf::RenderWindow(sf::VideoMode(900, 900), "olo - testing", sf::Style::Default);
}
Game::Game()
{
    this->initWindow();
}

Game::~Game()
{
	delete this->window;
}
//Methods
void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->Event))
    {
        if (this->Event.type == sf::Event::Closed)
            this->window->close();
    }
}
void Game::update()
{
    this->updateSFMLEvents();    
}
void Game::render()
{
    this->window->clear();

    //render items

    this->window->display();
}
void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }
}
