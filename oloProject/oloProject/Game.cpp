#include "Game.h"
 

//static methods

//Initialization methods
void Game::initVariables()
{
    this->Window = nullptr;
    this->isFullscreen = false;
    this->deltaTime = 0.f;
}
void Game::initWindow()
{
    std::ifstream ifs("Config/windowinit.txt");
    //what is this vector doing/used for?
    this->VideoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "windowinit.txt not found";
    sf::VideoMode window_Bounds = sf::VideoMode::getDesktopMode();;
    unsigned framerate_Limit = 120;
    bool vertical_Sync_Enabled = false;
    unsigned antialiasing_Level = 0;

    if (ifs.is_open()) 
    {
        std::getline(ifs, title);
        ifs >> window_Bounds.width >> window_Bounds.height;
        ifs >> this->isFullscreen;
        ifs >> framerate_Limit;
        ifs >> vertical_Sync_Enabled;
        ifs >> antialiasing_Level;
    }

    ifs.close();

    this->windowSettings.antialiasingLevel = antialiasing_Level;

    if(isFullscreen)
	    this->Window = new sf::RenderWindow(window_Bounds, title, sf::Style::Fullscreen, windowSettings);
    else
        this->Window = new sf::RenderWindow(window_Bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);

    this->Window->setFramerateLimit(framerate_Limit);
    this->Window->setVerticalSyncEnabled(vertical_Sync_Enabled);
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
    this->StatesStack.push(new MainMenuState(this->Window, &this->SupportedKeys, &this->StatesStack));

}

//Constructors/Destructions
Game::Game()
{
    this->initVariables();
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
