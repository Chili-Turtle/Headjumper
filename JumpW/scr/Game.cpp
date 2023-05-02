#include "stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Game 4", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::initPlayer()
{

	this->player = std::make_unique<Player>();
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollision()
{
	//Collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height);

		this->player->resetJump();
		this->player->resetJumptimerTimer();
	}

	////Collision right of screen
	if (this->player->getPosition().x + this->player->getGlobalBounds().width> this->window.getSize().x)
	{
		this->player->resetVelocityX();
		this->player->setPosition(
			this->window.getSize().y + this->player->getGlobalBounds().width/1.5,
			this->player->getPosition().y);
	}

	//// Collision Left of screen
	if (this->player->getPosition().x < 0)
	{
		this->player->resetVelocityX();
		this->player->setPosition(0, this->player->getPosition().y);
		
		//appear at the other side of the screen
		/*this->player->setPosition(
			this->window.getSize().y + this->player->getGlobalBounds().width / 2,
			this->player->getPosition().y);*/
	}
}

void Game::update()
{
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();

		if (
			this->ev.type == sf::Event::KeyReleased &&
			(
				this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S
				)
			)
		{
			this->player->resetAnimationTimer();
		}
	}

	this->updatePlayer();

	this->updateCollision();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	this->window.clear();

	//Render game
	this->renderPlayer();

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	// TODO: insert return statement here
	return this->window;
}