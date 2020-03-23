#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "Player.h"
#include "noise.h"
#include "Collision.h"
#include "Platform.h"
class Tile : public sf::RectangleShape{
    private:
    sf::RectangleShape tile;

    public:
        ~Tile(){};
        Collision GetCollision() { return Collision(tile); }
        Tile(){}
        void Draw(sf::RenderWindow& window) {
        	window.draw(tile);
        }
};

void initGrid(std::vector<std::vector<Tile> >& tileMap, int width, int height, float gridSizeF, sf::Texture* texture){
    tileMap.resize(width, std::vector<Tile>());
    // Initializes the grids
    for(int x = 0; x < width; x++){
        tileMap[x].resize(width);
        for(int y = 0; y < height; y++){
            tileMap[x][y].setSize(sf::Vector2f(gridSizeF,gridSizeF));
            tileMap[x][y].setTexture(texture);
            tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
        }
    }
}

void terrain1D(std::vector<std::vector<Tile> >& tileMap, int w, int h, int octave, float bias, float altitude){
    float fperlinNoise1D[w];
    float fnoiseSeed1D[w];
    for(int i = 0; i < w; i++)
    fnoiseSeed1D[i] = (float)rand()/(float)RAND_MAX;
    perlinNoise1D(w,fnoiseSeed1D, octave, fperlinNoise1D, bias);
    for(int x = 0; x < w; x++){
    int y = (fperlinNoise1D[x]* (float)h/altitude + (float)h/altitude);
    for(int f = h; f >= y; f--)
        tileMap[x][f].setFillColor(sf::Color::Black);
    }
}



//#endif
