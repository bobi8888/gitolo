#include "stdafx.h"

#include "Game.h" 

//static methods

//Clean up void Player::updateAnimation(const float& deltaTime)

//Make a resume game button in GameState Pause Menu

//Make enemies able to level up?

//Make a method for determining which animation should be played based on velocity. 
    //of if it should be based on which key is pressed?

//Initialization methods
void Game::initVariables()
{
    this->gameWindow = nullptr;

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
    this->stateData.stateDataWindow = this->gameWindow;
    this->stateData.graphicsSettings = &this->graphicSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.statesStack = &this->statesStack;
    this->stateData.gridSize = this->gridSize;
}

void Game::initWindow()
{
    if (this->graphicSettings.IsFullscreen)
	    this->gameWindow = new sf::RenderWindow(
            this->graphicSettings.Resolution,
            this->graphicSettings.Title,
            sf::Style::Fullscreen, 
            this->graphicSettings.ContextSettings
            );
    else
        this->gameWindow = new sf::RenderWindow(
            this->graphicSettings.Resolution,
            this->graphicSettings.Title,
            sf::Style::Titlebar | sf::Style::Close, 
            this->graphicSettings.ContextSettings
            );

    this->gameWindow->setFramerateLimit(this->graphicSettings.FramerateLimit);

    this->gameWindow->setVerticalSyncEnabled(this->graphicSettings.VsyncEnabled);
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
	delete this->gameWindow;

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
    while (this->gameWindow->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->gameWindow->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();   
    
    if (!this->statesStack.empty())
    {
        if (this->gameWindow->hasFocus())
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
    this->gameWindow->clear();

    //Rendering
    if (!this->statesStack.empty())
        this->statesStack.top()->render(this->gameWindow);

    this->gameWindow->display();
}

void Game::run()
{

    while (this->gameWindow->isOpen())
    {
        this->updateDeltaTime();

        this->update();

        this->render();
    }


        //sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Lighting with Ambient Light");
        //window.setVerticalSyncEnabled(true);
        // 
        //sprite for shader test
        //sf::Texture texture;
        //if (!texture.loadFromFile("sprite.png"))
        //{
        //    std::cerr << "Error: Could not load sprite.png" << std::endl;
        //}

        //sf::Sprite sprite(texture);
        //sprite.setPosition(100.f, 100.f);


        // Vertex shader: Passes texture coordinates to the fragment shader.
        //const std::string vertexShaderCode = R"(
        //    // Uniform texSize holds the texture size (in pixels)
        //    uniform vec2 texSize;

        //    void main()
        //    {
        //        // Normalize the texture coordinates by dividing by the texture size.
        //        vec2 normTexCoord = gl_MultiTexCoord0.xy / texSize;
        //        gl_TexCoord[0] = vec4(normTexCoord, 0.0, 1.0);

        //        // Standard vertex position transformation.
        //        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        //    }
        //)";

        // Fragment shader: Applies ambient and diffuse lighting.
        //const std::string fragmentShaderCode = R"(
        //    //Uniform texture is not set externally? Just declared here? Needed to work however
        //        uniform sampler2D texture;

        //    // Light position in normalized texture coordinate space [0, 1], set in while loop
        //        uniform vec2 lightPos; 
        //   
        //    // Light radius in texture coordinate space
        //        uniform float lightRadius;  

        //    // Color of the diffuse light
        //        uniform vec3 lightColor;    
        //    
        //    // Ambient light color
        //        uniform vec3 ambientLight;  

        //    void main()
        //    {
        //    // Sample the sprite's texture color.
        //        vec4 texColor = texture2D(texture, gl_TexCoord[0].xy);

        //    // Compute the distance from the current fragment to the light's position.
        //        float dist = distance(gl_TexCoord[0].xy, lightPos);

        //    // Calculate attenuation: fragments closer than the light radius are lit more intensely.
        //        float attenuation = clamp(1.0 - (dist / lightRadius), 0.0, 1.0);

        //    // Diffuse component scales with the attenuation.
        //        vec3 diffuse = lightColor * attenuation;

        //    // Combine ambient lighting with the diffuse component.
        //        vec3 finalLight = ambientLight + diffuse;

        //    // Multiply the texture color by the final light value.
        //        gl_FragColor = vec4(texColor.rgb * finalLight, texColor.a);
        //    }
        //)";

        //sf::Shader shader;
        //if (!shader.loadFromMemory(vertexShaderCode, fragmentShaderCode))
        //{
        //    std::cerr << "Error: Could not load shader" << std::endl;
        //}

        // Uniform texSize holds the texture size (in pixels)
        // Pass the texture size so the vertex shader can normalize texture coordinates (0-1).

    //is this the whole map? check and see where SS changed the map to sprites?
/*        sf::Vector2u texSize = texture.getSize();
        shader.setUniform("texSize", sf::Glsl::Vec2(static_cast<float>(texSize.x), static_cast<float>(texSize.y)));

        shader.setUniform("lightRadius", 0.5f);
        shader.setUniform("lightColor", sf::Glsl::Vec3(1.0f, 1.0f, 1.0f));  
        shader.setUniform("ambientLight", sf::Glsl::Vec3(0.5f, 0.5f, 0.5f));  */    

        //while (window.isOpen())
        //{
        //    sf::Event event;
        //    while (window.pollEvent(event))
        //    {
        //        if (event.type == sf::Event::Closed)
        //            window.close();
        //    }

//ALL THIS IS NEEDED IN THE UPDATE
            // Update the light position using the current mouse position.

        //should this be the map as well?
        //    sf::FloatRect spriteBounds = sprite.getGlobalBounds();

        ////This should be the player's position?
        //    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        //    // Convert mouse window coordinates to sprite-local normalized coordinates.
        //    float localX = (mousePos.x - spriteBounds.left) / spriteBounds.width;
        //    float localY = (mousePos.y - spriteBounds.top) / spriteBounds.height;

        //    shader.setUniform("lightPos", sf::Glsl::Vec2(localX, localY));
//ALL THIS IS NEEDED IN THE UPDATE

            //window.clear(sf::Color::Black);
            //window.draw(sprite, &shader);
            //window.display();
       

        //SS fragment_shader
        //in vec4 vert_pos;

        //uniform sampler2D texture; //unknown how this is being set? there is no setUniform for this?
        //uniform bool hasTexture;
        //uniform vec2 lightPos;

        //void main()
        //{
        //    //Ambient light
        //    //1.0f is max light, 0.0f is no light, the last value is alpha
        //    vec4 ambient = vec4(0.1f, 0.1f, 0.1f, 1.f);

        //    //Convert light to view coords
        //    vec2 lightPosTemp = lightPos;
        //    //gl_ModelViewProjectionMatrix can only be multiplied by a vec4?
        //    lightPosTemp = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0, 1)).xy;

        //    //Need to fix this to make the light circular
        //    //Calculate the vector from light to pixel (Make circular)
        //    vec2 lightToFrag = lightPosTemp - vert_pos.xy;

        //    //Length of the vector (distance)
        //    /*the factor multiplied against length(lightToFrag is the 'size of the light'
        //    2.0f is a larger light that 4.0f*/
        //    float vecLength = clamp(length(lightToFrag) * 2.0f, 0.0f, 1.0f);

        //    //lookup the pixel in the texture
        //    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

        //    //Muliply by the color & lighting
        //    if (hasTexture == true)
        //    {
        //        gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1 - vecLength, 1 - vecLength, 1 - vecLength, 1), 0.0f, 1.f));
        //    }
        //    else
        //    {
        //        gl_FragColor = gl_Color;
        //    }
        //}
    

}

void Game::endApplication()
{
    std::cout << "ending application" << "\n";
    this->gameWindow->close();
}
