#include "Spheres.h"



Spheres::Spheres(sf::RenderWindow &renderWindow, Player &player, float &DeltaTime) : DeltaTime(DeltaTime), player(player), renderWindow(renderWindow)
{
	texture.loadFromFile("resources/character/Magical-Orb.png");
	textureRect[0] = sf::IntRect(0, 0, 48, 48);
	textureRect[1] = sf::IntRect(48, 0, 48, 48);
	textureRect[2] = sf::IntRect(0, 48, 48, 48);
	textureRect[3] = sf::IntRect(48, 48, 48, 48);

	sprite.setOrigin(24, 24);

	sprite.setTexture(texture);
}


Spheres::~Spheres()
{
}

void Spheres::Follow() {
	if (alive) {

		if (clock.getElapsedTime().asSeconds() > 0.3) {
			if (textureInt < 3) {
				textureInt += 1;
			}
			else {
				textureInt = 0;
			}
			clock.restart();
		}

		sf::Vector2f position = sprite.getPosition();

		sprite.setTextureRect(sf::IntRect(textureRect[textureInt]));

		sf::Vector2f movement(0, 0);

		float deltaSpeed = DeltaTime * 300;

		if (position.x > player.position.x + 50) {
			movement.x -= deltaSpeed;
		}
		if (position.y < player.position.y + 40) {
			movement.y += deltaSpeed;
		}
		if (position.x < player.position.x - 50) {
			movement.x += deltaSpeed;
		}
		if (position.y > player.position.y + 20) {
			movement.y -= deltaSpeed;
		}

		sprite.move(movement);

		renderWindow.draw(sprite);

		if (sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
			player.currentHealth -= 5;
			alive = false;
		}
	}
	else {

		time += 6 * DeltaTime;
		if (time >= 10) {
			alive = false;
		}
	}
}