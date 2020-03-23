#include "Platform.h"

Platform::Platform(sf::Texture* texture, float gridSizeF, int xi, int yi) {
	body.setSize(sf::Vector2f(gridSizeF,gridSizeF));
	body.setTexture(texture);
	body.setFillColor(sf::Color::Red);
	body.setPosition(xi * gridSizeF, yi * gridSizeF);
	x = xi;
	y = yi;
}
Platform::~Platform() {
}

void Platform::Draw(sf::RenderWindow& window) {
	window.draw(body);
}
