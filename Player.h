#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collision.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	void Update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void shoot(int position,  float speed,sf::RenderWindow& window);


	void oncollision(sf::Vector2f direction);
	sf::Vector2f getPosition() { return body.getPosition(); }
	Collision GetCollision() { return Collision(body); }


private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool right;

	sf::Vector2f Velocity;
	bool canJump;
	float jumpHeight;
};

