#include "stdafx.h"
#include "GraphicsSettings.h"

//Constructors & Destructor
GraphicsSettings::GraphicsSettings()
{
	this->Title = "UNINITIALIZED";
	this->Resolution = sf::VideoMode::getDesktopMode();
	this->IsFullscreen = false;
	this->VsyncEnabled = false;
	this->FramerateLimit = 120;
	this->ContextSettings.antialiasingLevel = 0;
	this->VideoModes = sf::VideoMode::getFullscreenModes();
}

void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << this->Title;
		ofs << this->Resolution.width << " " << this->Resolution.height;
		ofs << this->IsFullscreen;
		ofs << this->FramerateLimit;
		ofs << this->VsyncEnabled;
		ofs << this->ContextSettings.antialiasingLevel;
	}

	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, this->Title);
		ifs >> this->Resolution.width >> this->Resolution.height;
		ifs >> this->IsFullscreen;
		ifs >> this->FramerateLimit;
		ifs >> this->VsyncEnabled;
		ifs >> this->ContextSettings.antialiasingLevel;
	}

	ifs.close();
}