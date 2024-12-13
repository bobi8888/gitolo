#include "Game.h"

//static methods

//Initializer methods
void Game::initWindow()
{
	//for gameplay
	// sf::RenderWindow window(sf::VideoMode(900, 900), "olo", sf::Style::None);
	
    std::ifstream ifs("Config/windowinit.txt");
    std::string title = "windowinit.txt not found";
    sf::VideoMode windowBounds(500, 500);
    unsigned framerateLimit = 120;
    bool verticalSyncEnabled = false;

    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> windowBounds.width >> windowBounds.height;
        ifs >> framerateLimit;
        ifs >> verticalSyncEnabled;
    }

    ifs.close();

	this->window = new sf::RenderWindow(windowBounds, title, sf::Style::Default);
    this->window->setFramerateLimit(framerateLimit);
    this->window->setVerticalSyncEnabled(verticalSyncEnabled);
}

void Game::initStates()
{
    this->States.push(new GameState(this->window));
}

//Constructors/Destructions
Game::Game()
{
    this->initWindow();
    this->initStates();
}

Game::~Game()
{
	delete this->window;

    while (!this->States.empty())
    {
        delete this->States.top();
        this->States.pop();
    }
}

void Game::endApplication()
{
    std::cout << "ending application" << "\n";
    this->window->close();
}

//Methods
void Game::updateDeltaTime()
{
    //updates deltaTime variable with the time it takes to update and render 1 frame
    this->deltaTime = this->deltaTimeClock.restart().asSeconds();

    //system("cls");
    //std::cout << this->deltaTime << "\n";
}
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
    
    if (!this->States.empty())
    {
        this->States.top()->update(this->deltaTime);

        if (this->States.top()->getQuit())
        {
            //Save game before quit
            this->States.top()->endState();
            delete this->States.top();
            this->States.pop();
        }
    }
    //Application End
    else {
        this->endApplication();
    }
}
void Game::render()
{
    this->window->clear();

    //Rendering
    if (!this->States.empty())
        this->States.top()->render(this->window);

    this->window->display();
}
void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDeltaTime();
        this->update();
        this->render();
    }
}
