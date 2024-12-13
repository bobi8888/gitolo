#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) 
	: State(window)
{

}

GameState::~GameState()
{

}

void GameState::endState()
{

}

void GameState::update(const float& deltaTime)
{
	std::cout << "this update is in GameState.cpp \n";
}

void GameState::render(sf::RenderTarget* target)
{

}
