#include <SFML/Graphics.hpp>

sf::View view;
sf::View setPlayerCoordForView(float x, float y) {
	float tempX = x; float tempY = y;
	if (x < 460) tempX = 460;
	if (x > 820) tempX = 820;
	if (y < 360) tempY = 360;
	if (y > 440) tempY = 440;	

	view.setCenter(tempX, tempY);


	return view;
}


