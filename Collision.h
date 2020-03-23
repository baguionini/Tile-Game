#pragma once
#include<SFML/Graphics.hpp>
#include <cmath>
class Collision
{
public:
	Collision(sf::RectangleShape& body);
	~Collision();

	void move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collision& Other,sf::Vector2f& direction, float push);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfsize() { return (body.getSize() / 2.0f); }

	
private:
	sf::RectangleShape& body;

};

