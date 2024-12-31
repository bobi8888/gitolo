#include "stdafx.h"

#include "Game.h" 

//static methods

//Initialization methods
void Game::initVariables()
{
    this->Window = nullptr;
    this->GameGraphicSettings.IsFullscreen = false;
    this->deltaTime = 0.f;
}
void Game::initGraphicsSettings()
{
    this->GameGraphicSettings.loadFromFile("Config/graphics.txt");
}

void Game::initWindow()
{
    if (this->GameGraphicSettings.IsFullscreen)
	    this->Window = new sf::RenderWindow(
            this->GameGraphicSettings.Resolution,
            this->GameGraphicSettings.Title,
            sf::Style::Fullscreen, 
            this->GameGraphicSettings.ContextSettings
            );
    else
        this->Window = new sf::RenderWindow(
            this->GameGraphicSettings.Resolution,
            this->GameGraphicSettings.Title,
            sf::Style::Titlebar | sf::Style::Close, 
            this->GameGraphicSettings.ContextSettings
            );

    this->Window->setFramerateLimit(this->GameGraphicSettings.FramerateLimit);

    this->Window->setVerticalSyncEnabled(this->GameGraphicSettings.VsyncEnabled);
}
void Game::initKeys()
{
    std::ifstream ifs("Config/supportedKeys.txt");

    if (ifs.is_open())
    {
        std::string key = "";
        int keyValue = 0;

        while (ifs >> key >> keyValue)
        {
            this->SupportedKeys[key] = keyValue;
        }
    }

    ifs.close();

    //DEBUGGING
    for (auto i : this->SupportedKeys)
    {
        std::cout << i.first << " : " << i.second << "\n";
    }
}
void Game::initStates()
{
    this->StatesStack.push(new MainMenuState(this->Window, this->GameGraphicSettings, &this->SupportedKeys, &this->StatesStack));
}

//Constructors/Destructions
Game::Game()
{
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStates();
}
Game::~Game()
{
	delete this->Window;

    while (!this->StatesStack.empty())
    {
        delete this->StatesStack.top();
        this->StatesStack.pop();
    }
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
    while (this->Window->pollEvent(this->Event))
    {
        if (this->Event.type == sf::Event::Closed)
            this->Window->close();
    }
}
void Game::update()
{
    this->updateSFMLEvents();   
    
    if (!this->StatesStack.empty())
    {
        this->StatesStack.top()->update(this->deltaTime);

        if (this->StatesStack.top()->getQuit())
        {
            //Save game before quit
            this->StatesStack.top()->endState();
            delete this->StatesStack.top();
            this->StatesStack.pop();
        }
    }
    //Application End
    else {
        this->endApplication();
    }
}
void Game::render()
{
    this->Window->clear();

    //Rendering
    if (!this->StatesStack.empty())
        this->StatesStack.top()->render(this->Window);

    this->Window->display();
}
void Game::run()
{
    while (this->Window->isOpen())
    {
        this->updateDeltaTime();
        this->update();
        this->render();

    }
}
void Game::endApplication()
{
    std::cout << "ending application" << "\n";
    this->Window->close();
}
