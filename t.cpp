#include "terrain.h"
static const float View_Size = 1000;

int main(void){
    float gridSizeF = 20.0f; // Gridsize of the map
    float viewSpeed = 1000.0f; // speed of view duh
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
	sf::RenderWindow window(sf::VideoMode(1000.0f, 1000.0f), "SFML GAME Window");
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(View_Size, View_Size));

    //std::vector<std::vector<Tile> > tileMap;
    std::vector<Platform> platform;
    std::vector<std::vector<Platform> > vert;
    const int height = 200;
    const int width = 200;
    // Initialize elements for cursor selection
    sf::Vector2i mouseScreen;
    sf::Vector2i mouseWindow;
    sf::Vector2f mouseView;
    sf::Vector2u mouseGrid;

    // Initialize click elements
    sf::Vector2i clickPos;

    // Object that selects a grid
    sf::RectangleShape cursor(sf::Vector2f(gridSizeF,gridSizeF));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineThickness(1.0f);
    cursor.setOutlineColor(sf::Color::Red);
    //initGrid(tileMap, width, height,gridSizeF, nullptr);


	float fnoiseSeed1D[width];
	float fperlinNoise1D[width];
	int octave = 7; // 1 - 7, oddly
	float bias = 1.50f;
	float altitude = 4.0f;
	for (int i = 0; i < width; i++)
		fnoiseSeed1D[i] = (float)rand() / (float)RAND_MAX;

	perlinNoise1D(width, fnoiseSeed1D, octave, fperlinNoise1D, bias);
	int y;
    vert.resize(width,std::vector<Platform>());
	for (int x = 0; x < width; x++) {
        vert[x].resize(height, Platform());
		y = (fperlinNoise1D[x] * float(height) / altitude + float(height) / altitude);
//        .resize(height, std::vector<Platform>();
		//platform.push_back(Platform(nullptr, gridSizeF, x, y));
        std::cout << y << ": " ;
		for (int f = height - 50; f >= y; f--) {
           //std::cout << f << " " ;
            vert[x][f].setTile(gridSizeF, x, f);
		}//std::cout << "\n";
	}
    //terrain1D(tileMap, width, height, octave, bias, altitude);

	//Textures
	sf::Texture playerTexture;
	playerTexture.loadFromFile("robotsprite.png");

	//animation
	Player player(&playerTexture, sf::Vector2u(10, 8), 0.05f, 300.0f, 200.0f);

	//collision
	Collision playerCollision = player.GetCollision();

	//clock
	float deltaTime = 0.0f;
	sf::Clock clock;
int color = 0;
    while (window.isOpen()){
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.f)
			deltaTime = 1.0f / 20.0f;

        mouseScreen = sf::Mouse::getPosition();
        mouseWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mouseView = window.mapPixelToCoords(mouseWindow);
        if(mouseView.x >= 0.f)
            mouseGrid.x = mouseView.x / gridSizeU;
        if(mouseView.y >= 0.f)
            mouseGrid.y = mouseView.y / gridSizeU;

        cursor.setPosition(mouseGrid.x * gridSizeF, mouseGrid.y * gridSizeF);

        sf::Event ev;

        while(window.pollEvent(ev)){
            switch(ev.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
            // Move the view

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                color += 1;

            if(color > 2)
                color = 0;
            // Click the tile

            switch(color){
                case 0:
                    cursor.setOutlineColor(sf::Color::Red);
                    break;
                case 1:
                    cursor.setOutlineColor(sf::Color::Blue);
                    break;
                case 2:
                    cursor.setOutlineColor(sf::Color::Yellow);
                    break;
                default:
                    break;
            }
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                if(vert[mouseGrid.x][mouseGrid.y].getColor() == sf::Color::White){
                    switch(color){
                        case 0:
                            vert[mouseGrid.x][mouseGrid.y].setColor(sf::Color::Red);
                            cursor.setOutlineColor(sf::Color::Red);
                            break;
                        case 1:
                            vert[mouseGrid.x][mouseGrid.y].setColor(sf::Color::Blue);
                            cursor.setOutlineColor(sf::Color::Blue);
                            break;
                        case 2:
                            vert[mouseGrid.x][mouseGrid.y].setColor(sf::Color::Yellow);
                            cursor.setOutlineColor(sf::Color::Yellow);
                            break;
                        default:
                            break;
                    }
                }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                vert[mouseGrid.x][mouseGrid.y].setColor(sf::Color::White);
            }

                

        }
        window.clear(sf::Color::White);
        player.Update(deltaTime);
        sf::Vector2f direction;
        for(int x = 0 ; x < width; x++){
            for(int y = 0; y < height; y++)
                if(vert[x][y].GetCollision().CheckCollision(playerCollision,direction,1.0f))
                    player.oncollision(direction);
        }

        view.setCenter(player.getPosition());

        window.setView(view);


        player.draw(window);
        // Draw tilemap
        for(int x = 0 ; x < width; x++){
            for(int y = 0; y < height; y++)
                vert[x][y].Draw(window);
        }




        window.draw(cursor);
        window.display();
    }
}
//g++ t.cpp Player.cpp Collision.cpp Platform.cpp Animation.cpp -o t -lsfml-graphics -lsfml-window -lsfml-system
