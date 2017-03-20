#ifndef OPTIONSET_H
#define OPTIONSET_H

#define SFML_NO_DEPRECATED_WARNINGS
#include <SFML/Graphics.hpp>
#include "pieces.h"

class optionSet {
public:
    optionSet() { getVideoModes(); loadOptions(); initBasePieces(); }

    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key rcw; // Rotate clockwise
    sf::Keyboard::Key rccw; // Rotate counter-clockwise
    sf::Keyboard::Key r180; // Rotate 180 degrees
    sf::Keyboard::Key hd; // Hard Drop
    sf::Keyboard::Key chat; // Activate chat
    sf::Keyboard::Key score; // Show score
    sf::Keyboard::Key away; // Go away

	//Abbreviations for these keys. c = column(or distance from left wall), r = rotation
	sf::Keyboard::Key c0r0;
	sf::Keyboard::Key c1r0;
	sf::Keyboard::Key c2r0;
	sf::Keyboard::Key c3r0;
	sf::Keyboard::Key c4r0;
	sf::Keyboard::Key c5r0;
	sf::Keyboard::Key c6r0;
	sf::Keyboard::Key c7r0;
	sf::Keyboard::Key c8r0;
	sf::Keyboard::Key c9r0;
	sf::Keyboard::Key c0r1;
	sf::Keyboard::Key c1r1;
	sf::Keyboard::Key c2r1;
	sf::Keyboard::Key c3r1;
	sf::Keyboard::Key c4r1;
	sf::Keyboard::Key c5r1;
	sf::Keyboard::Key c6r1;
	sf::Keyboard::Key c7r1;
	sf::Keyboard::Key c8r1;
	sf::Keyboard::Key c9r1;
	sf::Keyboard::Key c0r2;
	sf::Keyboard::Key c1r2;
	sf::Keyboard::Key c2r2;
	sf::Keyboard::Key c3r2;
	sf::Keyboard::Key c4r2;
	sf::Keyboard::Key c5r2;
	sf::Keyboard::Key c6r2;
	sf::Keyboard::Key c7r2;
	sf::Keyboard::Key c8r2;
	sf::Keyboard::Key c9r2;
	sf::Keyboard::Key c0r3;
	sf::Keyboard::Key c1r3;
	sf::Keyboard::Key c2r3;
	sf::Keyboard::Key c3r3;
	sf::Keyboard::Key c4r3;
	sf::Keyboard::Key c5r3;
	sf::Keyboard::Key c6r3;
	sf::Keyboard::Key c7r3;
	sf::Keyboard::Key c8r3;
	sf::Keyboard::Key c9r3;

	bool absolutePlacement;
    bool ghostpiece;
    bool fullscreen;
    bool sound;
    bool vSync;

    short MusicVolume;
    short EffectVolume;
    short ChatVolume;

    sf::Time repeatDelay;
    sf::Time repeatSpeed;

    sf::Time repeatDelayDown;
    sf::Time repeatSpeedDown;

    sf::Time frameDelay;
    sf::Time inputDelay;

    sf::Uint8 piecerotation[7];
    basePieces basepiece[7];

    sf::String name;

    std::vector<sf::VideoMode> modes;
    short currentmode;

    void getVideoModes();
    void initBasePieces();
    void loadOptions();
    void saveOptions();

    void setDelay(short, sf::String);
};

#endif