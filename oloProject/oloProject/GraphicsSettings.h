#pragma once

class GraphicsSettings
{
public:
	//Variables
	sf::VideoMode Resolution;
	bool IsFullscreen;
	bool VsyncEnabled;
	unsigned FramerateLimit;
	sf::ContextSettings ContextSettings;
	std::vector <sf::VideoMode> VideoModes;
	std::string Title;

	//Constructors & Destructor
	GraphicsSettings();

	//Methods
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};
