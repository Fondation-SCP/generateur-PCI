/**
 * Autrice : Cyrielle
 * Permet de générer toutes les combinaisons possibles des palettes de centres d’intérêt
 * en format .svg pour une image palette.svg telle que présente dans le dépôt.
 * /!\ Dépendance : librairie tinyxml2
 */
#include <iostream>
#include <tinyxml2.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace tinyxml2;

int main() {
	XMLDocument* doc = new XMLDocument();
	doc->LoadFile("palette.svg");
	std::string grey = "414141";
	std::vector<std::string> lettres = {"fanartiste", "staff", "auteur", "traducteur", "critique", "relecteur"};
	for(int i = 1; i <= 64; i++) {
		XMLDocument* neodoc = new XMLDocument();
		neodoc->LoadFile("palette.svg");
		XMLElement* g = neodoc->RootElement()->FirstChildElement("g");
		XMLElement* currentRect = g->FirstChildElement();
		std::vector<std::string> nom = std::vector<std::string>();
		for(int p = 0; p < 6; p++) {
			bool occult = i & (int) round(pow(2, p));
			if(occult) {
				currentRect->SetAttribute("style", ("fill:#" + grey + ";fill-opacity:0.996078;stroke:#2c2c2c;stroke-width:0.264583;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1").c_str());
			} else {
				nom.push_back(lettres[p]);
			}
			if(p < 5)
				currentRect = currentRect->NextSiblingElement();
		}
		std::string name = "";
		std::sort(nom.begin(), nom.end());
		for(std::string str : nom) {
			name += (name == "" ? "" : "-") + str;
		}
		
		neodoc->SaveFile(("Roles/" + name + ".svg").c_str());
		std::cout << "\rGénération : " << (i / 64.) * 100 << "%";
		delete(neodoc);
	}	
	delete(doc);
	return 0;
	
}
