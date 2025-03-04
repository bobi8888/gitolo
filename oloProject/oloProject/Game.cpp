#include "stdafx.h"

#include "Game.h" 

//static methods

//Clean up void Player::updateAnimation(const float& deltaTime)

//Make a resume game button in GameState Pause Menu

//Make enemies able to level up?

//EditorState not rendering TileMaps
//GameState IS rending TileMap...
//What is the difference between the 2?
//Editor state only renders type 5???

//Make a method for determining which animation should be played based on velocity. 
    //of if it should be based on which key is pressed?

//Initialization methods
void Game::initVariables()
{
    this->window = nullptr;

    this->graphicSettings.IsFullscreen = false;

    this->deltaTime = 0.f;

    this->gridSize = 50.f;
}

void Game::initGraphicsSettings()
{
    this->graphicSettings.loadFromFile("Config/graphics.txt");
}

void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.graphicsSettings = &this->graphicSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.statesStack = &this->statesStack;
    this->stateData.gridSize = this->gridSize;
}

void Game::initWindow()
{
    if (this->graphicSettings.IsFullscreen)
	    this->window = new sf::RenderWindow(
            this->graphicSettings.Resolution,
            this->graphicSettings.Title,
            sf::Style::Fullscreen, 
            this->graphicSettings.ContextSettings
            );
    else
        this->window = new sf::RenderWindow(
            this->graphicSettings.Resolution,
            this->graphicSettings.Title,
            sf::Style::Titlebar | sf::Style::Close, 
            this->graphicSettings.ContextSettings
            );

    this->window->setFramerateLimit(this->graphicSettings.FramerateLimit);

    this->window->setVerticalSyncEnabled(this->graphicSettings.VsyncEnabled);
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
            this->supportedKeys[key] = keyValue;
        }
    }

    ifs.close();

    //DEBUGGING
    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " : " << i.second << "\n";
    }
}

void Game::initStates()
{
    this->statesStack.push(new MainMenuState(&this->stateData));
}

//Constructors/Destructions
Game::Game()
{
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{
	delete this->window;

    while (!this->statesStack.empty())
    {
        delete this->statesStack.top();
        this->statesStack.pop();
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
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();   
    
    if (!this->statesStack.empty())
    {
        if (this->window->hasFocus())
        {
            this->statesStack.top()->update(this->deltaTime);

            if (this->statesStack.top()->getQuit())
            {
                //Save game before quit
                this->statesStack.top()->endState();

                delete this->statesStack.top();

                this->statesStack.pop();
            }
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
    if (!this->statesStack.empty())
        this->statesStack.top()->render(this->window);

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

    //GLFWwindow* window;

    ///* Initialize the library */
    //if (!glfwInit())
    //    std::cout << "INIT ERROR" << "\n";

    ///* Create a windowed mode window and its OpenGL context */
    //window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    //if (!window)
    //{
    //    glfwTerminate();
    //    std::cout << "WINDOW ERROR" << "\n";
    //}

    ///* Make the window's context current */
    //glfwMakeContextCurrent(window);

    ///* Loop until the user closes the window */
    //while (!glfwWindowShouldClose(window))
    //{
    //    /* Render here */
    //    glClear(GL_COLOR_BUFFER_BIT);

    //    glBegin(GL_TRIANGLES);
    //    glVertex2f(-0.5f, -0.5f);
    //    glVertex2f(0.0f, 0.5f);
    //    glVertex2f(0.5f, -0.5f);
    //    glEnd();

    //    /* Swap front and back buffers */
    //    glfwSwapBuffers(window);

    //    /* Poll for and process events */
    //    glfwPollEvents();
    //}

    //glfwTerminate();
}

void Game::endApplication()
{
    std::cout << "ending application" << "\n";
    this->window->close();
}
