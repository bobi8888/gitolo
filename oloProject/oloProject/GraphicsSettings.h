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

/* 
List of my resolutions
3840 x 2160
3200 x 1800
3072 x 1728
2560 x 1440
2048 x 1536
1920 x 1200
1920 x 1080
1760 x 990
1680 x 1050
1600 x 1200
1660 x 900
1440 x 576
1440 x 480
1366 x 786
1280 x 1024
1280 x 720
1128 x 634
1024 x 768
800 x 600
720 x 576
720 x 480
640 x 480
*/