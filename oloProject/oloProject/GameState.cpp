#include "stdafx.h"

#include "GameState.h"

//Initializer Methods
void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->graphicsSettings->Resolution.width,
		this->stateData->graphicsSettings->Resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());

	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 0, 
			this->stateData->graphicsSettings->Resolution.width, 
			this->stateData->graphicsSettings->Resolution.height
		)
	);

}

void GameState::initView()
{
	this->testView = new sf::View();
	
	this->view.setSize(
		static_cast<float>(this->stateData->graphicsSettings->Resolution.width),
		static_cast<float>(this->stateData->graphicsSettings->Resolution.height)
	);

	this->view.setCenter(		
		this->stateData->graphicsSettings->Resolution.width / 2.f,
		this->stateData->graphicsSettings->Resolution.height / 2.f		
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestateKeybinds.txt");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/RobotoCondensed-Regular.ttf"))
	{
		throw("ERROR::MainMenuState::Could not load font.");
	}
}

void GameState::initTextures()
{
	if (!this->texturesMap["ROBO_100"].loadFromFile(
		"Resources/Images/Sprites/Robo/ROBO_100.png"
		)
	)
	
	throw("ERROR::GameState::COULD_NOT_LOAD_PLAYER_TEXTURE");
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(this->stateData->graphicsSettings->Resolution, this->font);

	const sf::VideoMode& videoMode = this->stateData->graphicsSettings->Resolution;

	this->pauseMenu->addButton(
		gui::convertToPixelsX(50.f, videoMode), gui::convertToPixelsY(65.f, videoMode),
		gui::convertToPixelsX(12.f, videoMode), gui::convertToPixelsY(5.f, videoMode),
		"QUIT", "Quit Game", gui::calculateCharSize(videoMode, 75)
		);
}

void GameState::initShaders()
{
	//Make this work 
	const std::string vertexShaderCode = R"(
        uniform vec2 texSize; //texture size (in pixels)

        void main()
        {            
            vec2 normTexCoord = gl_MultiTexCoord0.xy / texSize; // Normalize texture coords by dividing by the texture size.
            gl_TexCoord[0] = vec4(normTexCoord, 0.0, 1.0);

            gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; // Standard vertex position transformation.
        }
    )";

	const std::string fragmentShaderCode = R"(
        uniform sampler2D texture; // A declaration needed to work

        uniform vec2 lightPos; // SET IN UPDATE: Light position in normalized texture coordinate space [0, 1]
           
        uniform float lightRadius; // Light radius in texture coordinate space

        uniform vec3 playerLightColor; // Color of the light coming from the player
		            
        uniform vec3 ambientLight;  

        void main()
        {
            vec4 texColor = texture2D(texture, gl_TexCoord[0].xy); // Sample the sprite's texture color.

            float dist = distance(gl_TexCoord[0].xy, lightPos); // Compute dist from current fragment to light's pos.

            float attenuation = clamp(1.0 - (dist / lightRadius), 0.0, 1.0); // Calc attenuation: 
			                                                                 // fragments closer than the light 
																			 // radius are lit more intensely.

            vec3 diffuse = playerLightColor * attenuation; // Diffuse component scales with the attenuation.

            vec3 finalLight = ambientLight + diffuse; // Combine ambient lighting with the diffuse component.

            gl_FragColor = vec4(texColor.rgb * finalLight, texColor.a); // Multiply the texture color by the final light value.
        }
    )";

	if (!mainShader.loadFromMemory(vertexShaderCode, fragmentShaderCode))
	{
		std::cerr << "Error: Could not load shader" << std::endl;
	}

		if (!this->testTexture.loadFromFile("rock.png"))
		{
			std::cerr << "Error: Could not load sprite.png" << std::endl;
		}

		this->testSprite.setTexture(this->testTexture);

		this->testSprite.setPosition(500.f, 500.f);

	//this is what is getting the light applied to it
		sf::Vector2u texSize = this->testSprite.getTexture()->getSize();
		//sf::Vector2u texSize = sf::Vector2u(
		//	static_cast<unsigned>(this->tileMap->getGridMaxSizeInt().x),
		//	static_cast<unsigned>(this->tileMap->getGridMaxSizeInt().y)
		//);

	mainShader.setUniform("texSize", sf::Glsl::Vec2(static_cast<float>(texSize.x), static_cast<float>(texSize.y)));
	mainShader.setUniform("lightRadius", 0.5f);
	mainShader.setUniform("playerLightColor", sf::Glsl::Vec3(0.9f, 0.9f, 0.9f));
	mainShader.setUniform("ambientLight", sf::Glsl::Vec3(0.5f, 0.5f, 0.5f));

}

void GameState::initPlayers()
{
	this->player = new Player(this->texturesMap["ROBO_100"], 0, 0);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->graphicsSettings->Resolution);
}

void GameState::initTileMap()
{
	//this declaration is working for the EditorState
	//this->tileMap = new TileMap(
	//	this->stateData->gridSize, 
	//	25, 25, 
	//	//this->tileToolTextureRect, 
	//	"Resources/Images/Tiles/tiles50.png"
	//);

	//This is giving an error
	//this->tileMap->loadFromFile("editorTileMap.txt");
	
	//This is maping the textures weird, grass is ok, other tiles are smaller? 
	//Collision works, but the tile sheet is taking some sort of ratio instead of 50 x 50 pxl
	//This declaration works fine in editorState
	this->tileMap = new TileMap("editorTileMap.txt");
}

void GameState::initTransitionComponents()
{
	this->transitionComponent = new TransitionComponent();

	//const sf::VideoMode& videoMode = this->stateData->graphicsSettings->Resolution;

	this->transitionComponent->addTransitionZone(
		"MECHANICS_DOOR", 
		550.f, 400.f,
		50.f, 50.f
	);
}

//Constructors & Destructors
GameState::GameState(StateData* stateData, std::string name)
	: State(stateData)
{
	this->name = name;

	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();

	//this->initShaders();

	this->initPlayers();

	this->initTileMap();
	this->initShaders();

	this->initPlayerGUI();

	this->initTransitionComponents();

	//DEBUG
	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(18);
}

GameState::~GameState()
{
	delete this->player;

	delete this->playerGUI;

	delete this->pauseMenu;

	delete this->tileMap;

	delete this->transitionComponent;

	std::cout << "GameState deleted" << "\n";
}

void GameState::updateTransitions(const float& deltaTime)
{
	//how are states launched in main menu?
}

//Methods
 
//void GameState::updateView(const float& deltaTime)
void GameState::updateView()
{
	//std::floor helps with screen tearing because using float values makes it hard to be pixel perfect
	//look into this for a better explaination
	this->view.setCenter(
		//move camera with player movement
		std::floor(this->player->getHitboxPosition().x 
			//move camera with mouse movement
			+ (static_cast<float>(this->mousePositionWindow.x) 
			- static_cast<float>(this->stateData->graphicsSettings->Resolution.width / 2)) / 10.f),
		//move camera with player movement
		std::floor(this->player->getHitboxPosition().y 
			//move camera with mouse movement
			+ (static_cast<float>(this->mousePositionWindow.y)
			- static_cast<float>(this->stateData->graphicsSettings->Resolution.height / 2)) / 10.f)
	);

	if (this->tileMap->getGridMaxSizeFloat().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getGridMaxSizeFloat().x)
			this->view.setCenter(this->tileMap->getGridMaxSizeFloat().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
	}

	if (this->tileMap->getGridMaxSizeFloat().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getGridMaxSizeFloat().y)
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getGridMaxSizeFloat().y - this->view.getSize().y / 2.f);
	}

	this->viewGridPosition.x = static_cast<int>(
		this->view.getCenter().x / this->stateData->gridSize
	);

	this->viewGridPosition.y = static_cast<int>(
		this->view.getCenter().y / this->stateData->gridSize
	);
}

//void GameState::updateInput(const float& deltaTime)
void GameState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->isPaused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, deltaTime);
}

//void GameState::updatePlayerGUI(const float& deltaTime)
//{
//	//this->playerGUI->update(deltaTime, this->view.getCenter());
//	//this->playerGUI->update(deltaTime, this->player->getSpritePosition());
//}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& deltaTime)
{
	this->tileMap->updateCollision(this->player, deltaTime);
}

void GameState::updateShader()
{
	//start by putting the test sprite in the center of the map and make the light position be the player

	//Whats getting lit
	sf::FloatRect spriteBounds = this->testSprite.getGlobalBounds();

	//Light position
	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->stateWindow);

	// Convert mouse window coordinates to sprite-local normalized coordinates.
	float localX = (mousePos.x - spriteBounds.left) / spriteBounds.width;

	float localY = (mousePos.y - spriteBounds.top) / spriteBounds.height;

	std::cout << localX << " " << localY <<  "\n";

	mainShader.setUniform("lightPos", sf::Glsl::Vec2(localX, localY));
}

void GameState::update(const float& deltaTime)
{
	this->updateShader();
		
	this->updateMousePositions(&this->view);

	this->updateKeytime(deltaTime);

	//this->updateInput(deltaTime);
	this->updateInput();

	//DEBUG
	this->cursorText.setPosition(
		sf::Vector2f(
			static_cast<float>(this->mousePositionWindow.x), 
			static_cast<float>(this->mousePositionWindow.y) + 15.f
		)
	);

	std::stringstream ss;

	ss << this->mousePositionView.x << "  " << this->mousePositionView.y << "\n";

	this->cursorText.setString(ss.str());

	if (!this->isPaused)
	{
		//this->updateView(deltaTime);
		this->updateView();

		this->updatePlayerInput(deltaTime);

		this->updateTileMap(deltaTime);

		this->player->update(deltaTime, this->mousePositionView);

		this->playerGUI->update(deltaTime);
	}
	else
	{
		this->pauseMenu->update(this->mousePositionWindow);

		this->updatePauseMenuButtons();
	}
		
		this->transitionComponent->update(this->player->getHitboxGlobalBounds());
}

void GameState::render(sf::RenderTarget* target)
{	
	if(!target)
		target = this->stateWindow;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->render(
		this->renderTexture, 
		this->viewGridPosition,
		//&this->mainShader,
		NULL,
		this->player->getSpriteCenter(),
		false
		);
	
	//this->player->render(this->renderTexture, &this->mainShader, true);
	this->player->render(this->renderTexture, NULL, true);

	this->tileMap->renderDeferred(
		this->renderTexture, 
		//&this->mainShader,
		NULL,
		this->player->getSpriteCenter()
	);

		

	this->transitionComponent->render(this->renderTexture);

	this->playerGUI->render(this->renderTexture);

	this->renderTexture.setView(this->renderTexture.getDefaultView());


	if (this->isPaused)
	{
		this->pauseMenu->render(this->renderTexture);
	}

	//Final Render
	this->renderTexture.display();

	this->renderSprite.setTexture(this->renderTexture.getTexture());

	target->draw(this->renderSprite);
		
target->draw(this->testSprite, &mainShader);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		//Debugging

		//target->draw(mouse_text);
		//sf::Text mouse_text;
		//mouse_text.setPosition(sf::Vector2f(this->mousePositionView.x, this->mousePositionView.y + 15));
		//mouse_text.setFont(this->font);
		//mouse_text.setCharacterSize(18);
		//std::stringstream ss;
		//ss << this->mousePositionView.x << "  " << this->mousePositionView.y;
		//mouse_text.setString(ss.str());

		target->draw(this->cursorText);
	}	
}
