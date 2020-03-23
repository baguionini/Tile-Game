#include "Player.h"
#include <iostream>
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight)
	:animation(texture,imageCount,switchTime)
{
	this->jumpHeight = jumpHeight;
	this->speed = speed;
	row = 0;
	right = true;

	body.setSize(sf::Vector2f(50.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(0.0f, 0.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	bool isshoot = false, isMelee = false, isRun = false ,isjump = false;
	float gravity = 981.0f;
	//sf::Vector2f movement(0.0f, 0.0f);
	Velocity.x *= 0.5f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		Velocity.x -= speed;
		isRun = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		Velocity.x += speed ;
		isRun = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)&&canJump) {
		canJump = false;
		Velocity.y = -sqrt(2.0f * gravity * jumpHeight);
		isjump = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		isshoot = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		isMelee = true;
	}
	
	Velocity.y += gravity * deltaTime;

	if (Velocity.x == 0) {
		row = 0;
		speed = 100.0f;
	}
	else {
		if (Velocity.x > 0) {
			right = true;
		}
		else {
			right = false;
		}
	}
	if (isjump)
		row = 2;
	else if (isRun)
		row = 1;
	else if (isshoot) {
		row = 4;
	}
	else if (isMelee)
		row = 5;
	else
		row = 0;
	if(isshoot&&isRun)
		row = 6;

	animation.Update(row, deltaTime, right);
	body.setTextureRect(animation.uvRect);
	body.move(Velocity*deltaTime);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);
}
void Player::shoot(int position, float speed,sf::RenderWindow& window) {
	
}

void Player::oncollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f) {
		//collision on left
		Velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		//collision on right
		Velocity.x = 0.0f;
	}
	if (direction.y < 0.0f) {
		//collision on bottom
		Velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f) {
		//collision on top
		Velocity.y = 0.0f;
		
	}
}
