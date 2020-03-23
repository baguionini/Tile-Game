#include "Collision.h"


Collision::Collision(sf::RectangleShape& body):
	body(body)
{
}

Collision::~Collision()
{
}


bool Collision::CheckCollision(Collision& other,sf::Vector2f& direction, float push) {
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfsize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfsize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - ((otherHalfSize.x-10) + thisHalfSize.x);
	float intersectY = abs(deltaY) - ((otherHalfSize.y-10) + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f) {


		push = std::min(std::max(push, 0.0f), 1.0f);//clumping
		if (intersectX > intersectY) {
			if (deltaX > 0.0f) {
				move(intersectX * (1.0f - push), 0.0f);
				other.move(-intersectX * push, 0.0f);

				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else {
				move(-intersectX * (1.0f - push), 0.0f);
				other.move(intersectX * push, 0.0f);


				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else {
			if (deltaY > 0.0f) {
				move(0.0f,intersectY * (1.0f - push));
				other.move( 0.0f ,-intersectY * push);


				direction.y = 1.0f;
				direction.x = 0.0f;
			}
			else {
				move(0.0f ,-intersectY * (1.0f - push));
				other.move(0.0f,intersectY * push);

				direction.y = -1.0f;
				direction.x = 0.0f;
			}
		}
		return true;
	}

	return false;
}