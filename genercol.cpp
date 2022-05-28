/**
 * Autrice : Cyrielle
 * Permet de générer toutes les combinaisons possibles des palettes de centres d’intérêt
 * en format .png pour une image palette.png telle que présente dans le dépôt.
 * /!\ Dépendance : librairie SFML
 */
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

int main() {
	sf::Image img = sf::Image();
	img.loadFromFile("palette.png");
	sf::Uint32 grey = 0x414141FF;
	std::vector<sf::Vector2i> rectangles = std::vector<sf::Vector2i>();
	for(int i = 0; i < 6; i++) {
		rectangles.push_back(sf::Vector2i((i % 2 == 0) ? 1 : 4, ((i / 2) * 5) +1));
	}
	sf::Vector2i recsize = sf::Vector2i(2, 4);
	std::vector<std::string> lettres = {"fanartiste", "staff", "auteur", "traducteur", "critique", "relecteur"};
	for(int i = 1; i <= 64; i++) {
		sf::Image nimg = img;
		std::vector<std::string> nom = std::vector<std::string>();
		for(int p = 0; p < 6; p++) {
			bool occult = i & (int) round(pow(2, p));
			if(occult) {
				for(int x = rectangles[p].x; x < rectangles[p].x + recsize.x; x++) {
					for(int y = rectangles[p].y; y < rectangles[p].y + recsize.y; y++) {
						nimg.setPixel(x,y,sf::Color(grey));
					}
				}
			} else {
				nom.push_back(lettres[p]);
			}
		}
		std::string name = "";
		std::sort(nom.begin(), nom.end());
		for(std::string str : nom) {
			name += (name == "" ? "" : "-") + str;
		}
		
		nimg.saveToFile("Roles/" + name + ".png");
		std::cout << "\rGénération : " << (i / 64.) * 100 << "%";
	}	
	return 0;
	
}
