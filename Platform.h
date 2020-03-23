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
		body.setSize(sf::Vector2f(gridSizeF,gridSizeF));
		body.setPosition(xi * gridSizeF, yi * gridSizeF);
		body.setFillColor(sf::Color::Black);
		//body.setTexture(nullptr
	}
	void setColor(sf::Color color){body.setFillColor(color);}
	void Draw(sf::RenderWindow& window);
	sf::Color getColor(){return body.getFillColor();}
	Collision GetCollision() { return Collision(body); }
	int getX(){return x;};
	int getY(){return y;}
private:
	sf::RectangleShape body;
	int x, y;
};
//git push master withCollision