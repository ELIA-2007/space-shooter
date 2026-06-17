#include "Game.h"

void Game::initWindow() {
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	unsigned int width = desktop.width * 0.4f;
	unsigned int height = desktop.height * 0.9f;

	this->window = new sf::RenderWindow(sf::VideoMode(width, height), "SpaceShooter", sf::Style::Close | sf::Style::Titlebar);
	this->deltaClock;

	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
	
	this->debug = false;

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

void Game::initFonts() {
	if (this->fonts["MAIN"].loadFromFile("fonts/JetBrainsMonoNL-Regular.ttf")) {
		std::cout << "ERROR::GAME::INITFONT:: Could not load font file." << "\n";
	}
	else {
		std::cout << "Font caricato con successo!" << "\n";
	}
}

void Game::initPlayer() {
	this->player = new Player(this->textures["PLAYER"], this->window->getSize());
	this->player->setPosition(static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) - this->player->getSize().y);
}

//Constructor / Destructor
Game::Game() {
	this->initWindow();
	this->initTextures();
	this->initFonts();
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
		this->dtTime = deltaClock.restart();
		this->dt = dtTime.asSeconds();
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
	this->player->direction.x = 0; this->player->direction.y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->player->getPos().x > 0) {
		this->player->direction.x += -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (this->player->getPos().x + this->player->getSize().x) < this->window->getSize().x) {
		this->player->direction.x += +1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->player->getPos().y > 0) {
		this->player->direction.y += -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (this->player->getPos().y + this->player->getSize().y) < this->window->getSize().y) {
		this->player->direction.y += +1;
	}

	normalizeVector(&this->player->direction);
	this->player->move(this->player->direction, this->dt);

	if (this->player->canAttack())
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->window->getSize(), this->player->getPos().x + (this->player->getSize().x / 2), this->player->getPos().y, 0.f, -1.f, 500.f));
	
	if (this->f1KeyCooldown > 0)
		--this->f1KeyCooldown;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && this->f1KeyCooldown == 0) {
		this->f1KeyCooldown = 80;
		this->debug = !this->debug;
	}
}

void Game::updateBullets() {
	for (int i = static_cast<int>(this->bullets.size()) - 1; i >= 0; --i) {
		this->bullets[i]->update(this->dt);

		// Bullet culling (top of screen)
		if (this->bullets[i]->getBounds().top + this->bullets[i]->getBounds().height < 0.f) {
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin() + i);
			continue;
		}

		//Check collisions
		for (int j = static_cast<int>(this->enemies.size()) - 1; j >= 0; --j) {
			if (this->bullets[i]->getBounds().intersects(this->enemies[j]->getBounds())) {
				delete this->bullets[i];
				this->bullets.erase(this->bullets.begin() + i);
				this->enemies[j]->getHit(this->player->getDamage());
				break;
			}
		}
	}
}

void Game::updateAsteroids() {
	for (int i = static_cast<int>(this->enemies.size()) - 1; i >= 0; --i) {
		this->enemies[i]->update(this->dt);

		// Asteroid culling (bottom of screen or destroyed)
		if (this->enemies[i]->getBounds().top + this->enemies[i]->getBounds().height > this->window->getSize().y or this->enemies[i]->getHealth() <= 0) {
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
	//std::cout << this->enemies.size() << "\n";
}

void Game::spawnEnemies() {
	this->spawning += dt;
	if (this->spawning >= this->spawnRate) {
		this->enemies.push_back(new Asteroid(this->textures["ASTEROID"], this->window->getSize()));
		this->spawning -= this->spawnRate;
	}
}

void Game::update() {
	this->updatePollEvents();
	this->updateInput();
	this->player->update(this->dt);

	for (int i = static_cast<int>(this->enemies.size()) - 1; i >= 0; --i) {
		if (this->player->getBounds().intersects(this->enemies[i]->getBounds())) {
			this->player->getHit(this->enemies[i]->getDamage());
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
	if (this->player->getHealth() <= 0) {
		this->window->close();
	}

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

	for (auto* enemy : this->enemies)
		enemy->render(*this->window);

	if (this->debug) {
		sf::FloatRect bounds = this->player->getBounds();
		drawHitbox(bounds, sf::Color::Green, *this->window);

		for (auto* enemy : this->enemies) {
			sf::FloatRect bounds = enemy->getBounds();
			drawHitbox(bounds, sf::Color::Red, *this->window);
		}

		for (auto* bullet : this->bullets) {
			sf::FloatRect bounds = bullet->getBounds();
			drawHitbox(bounds, sf::Color::Blue, *this->window);
		}
	}

	text(this->fonts["MAIN"], "DIOCANE", 40, sf::Color::White, 100, 100, *this->window);

	this->window->display();
}