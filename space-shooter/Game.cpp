#include "Game.h"

void Game::initWindow() {
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	unsigned int width = desktop.width * 0.4f;
	unsigned int height = desktop.height * 0.9f;

	this->window = new sf::RenderWindow(sf::VideoMode(width, height), "SpaceShooter", sf::Style::Close | sf::Style::Titlebar);

	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);

	std::cout << width << "  " << height << "\n";
}

void Game::initTextures() {
	//Background
	if (!this->backgroundTexture.loadFromFile("assets/background.png"))
		std::cout << "ERROR::GAME::INITTEXTURES:: Could not load background texture file." << "\n";
	this->backgroundSprite.setTexture(this->backgroundTexture);
	this->backgroundSprite.setScale(static_cast<float>(this->window->getSize().x) / this->backgroundTexture.getSize().x, static_cast<float>(this->window->getSize().y) / this->backgroundTexture.getSize().y);

	//Player
	this->textures["PLAYER"] = new sf::Texture();
	if (!this->textures["PLAYER"]->loadFromFile("assets/space-ship.png"))
		std::cout << "ERROR::GAME::INITTEXTURE:: Could not load player texture file." << "\n";

	//Bullets
	this->textures["BULLET"] = new sf::Texture();
	if (!this->textures["BULLET"]->loadFromFile("assets/bullet.png"))
		std::cout << "ERROR::GAME::INITTEXTURE:: Could not load bullet texture file." << "\n";

	//Asteroids
	this->textures["ASTEROID"] = new sf::Texture();
	if (!this->textures["ASTEROID"]->loadFromFile("assets/asteroid1.png"))
		std::cout << "ERROR::GAME::INITTEXTURE:: Could not load asteroid texture file." << "\n";

}

void Game::initPlayer() {
	this->player = new Player(this->textures["PLAYER"], this->window->getSize());
	this->player->setPosition(static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) - this->player->getSize().y);
}

//Constructor / Destructor
Game::Game() {
	this->initWindow();
	this->initTextures();
	this->initPlayer();
}

Game::~Game() {
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
		delete i.second;

	//Delete bullets
	for (auto* i : this->bullets)
		delete i;
}

//Functions
void Game::run() {
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}

void Game::updatePollEvents() {
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput() {
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->player->getPos().x > 0)
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (this->player->getPos().x + this->player->getSize().x) < this->window->getSize().x)
		this->player->move(+1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->player->getPos().y > 0)
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (this->player->getPos().y + this->player->getSize().y) < this->window->getSize().y)
		this->player->move(0.f, +1.f);

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and this->player->canAttack()) {
	//	this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + (this->player->getSize().x / 2), this->player->getPos().y, 0.f, -1.f, 3.f));
	//}
	if (this->player->canAttack())
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->window->getSize(), this->player->getPos().x + (this->player->getSize().x / 2), this->player->getPos().y, 0.f, -1.f, 3.f));
}

void Game::updateBullets() {
	for (int i = static_cast<int>(this->bullets.size()) - 1; i >= 0; --i) {
		this->bullets[i]->update();

		// Bullet culling (top of screen)
		if (this->bullets[i]->getBounds().top + this->bullets[i]->getBounds().height < 0.f) {
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin() + i);
		}
	}
}

void Game::updateAsteroids() {
	for (int i = static_cast<int>(this->asteroids.size()) - 1; i >= 0; --i) {
		this->asteroids[i]->update();

		// Asteroid culling (bottom of screen)
		if (this->asteroids[i]->getBounds().top + this->asteroids[i]->getBounds().height > this->window->getSize().y) {
			delete this->asteroids[i];
			this->asteroids.erase(this->asteroids.begin() + i);
		}
		std::cout << this->asteroids.size() << "\n";
	}
}

void Game::spawnEnemies() {
	if (this->spawning >= this->spawnRate) {
		this->asteroids.push_back(new Asteroid(this->textures["ASTEROID"], this->window->getSize()));
		this->spawning = 0;
	}
	else
		++this->spawning;
}

void Game::update() {
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateBullets();
	this->updateAsteroids();
	this->spawnEnemies();
}

void Game::render() {
	this->window->clear();
	this->window->draw(this->backgroundSprite);

	//Draw everything here
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
		bullet->render(this->window);

	for (auto* asteroid : this->asteroids)
		asteroid->render(*this->window);

	this->window->display();
}