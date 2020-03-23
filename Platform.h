#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
class Platform :public sf::RectangleShape
{
public:
	Platform(sf::Texture* texture, float gridSizeF, int xi, int yi);
	Platform(){}
	~Platform();
	void setTile(float gridSizeF, int xi, int yi){
		body.setPosition(xi * gridSizeF, yi * gridSizeF);
		body.setFillColor(sf::Color::White);
		//body.setTexture(nullptr);
		
	}
	void Draw(sf::RenderWindow& window);
	Collision GetCollision() { return Collision(body); }
	int getX(){return x;};
	int getY(){return y;}
private:
	sf::RectangleShape body;
	int x, y;
};
