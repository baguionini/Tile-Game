#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture* texture,sf::Vector2u imageCount,float switchTime);
	~Animation();

	void Update(int row, float deltaTime, bool right);

public://variables
	sf::IntRect uvRect;


private://variables
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;
};

