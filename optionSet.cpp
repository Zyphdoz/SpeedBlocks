#include "optionSet.h"
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "MingwConvert.h"
using namespace std;

#ifdef __APPLE__
#include "ResourcePath.hpp"
#else
#include "EmptyResourcePath.h"
#endif

void optionSet::loadOptions() {
	string line;
	ifstream file (resourcePath() + "options.cfg");

	int countset = 0;

	bool success = 1;

	if (file.is_open()) {
		while (getline(file, line)) {
			switch (countset) {
				case 0: down = sf::Keyboard::Key(stoi(line)); break;
				case 1: left = sf::Keyboard::Key(stoi(line)); break;
				case 2: right = sf::Keyboard::Key(stoi(line)); break;
				case 3: rcw = sf::Keyboard::Key(stoi(line)); break;
				case 4: rccw = sf::Keyboard::Key(stoi(line)); break;
				case 5: r180 = sf::Keyboard::Key(stoi(line)); break;
				case 6: hd = sf::Keyboard::Key(stoi(line)); break;
				case 7: chat = sf::Keyboard::Key(stoi(line)); break;
				case 8: score = sf::Keyboard::Key(stoi(line)); break;
				case 9: away = sf::Keyboard::Key(stoi(line)); break;
				case 10: ghostpiece = stoi(line); break;
				case 11: fullscreen = stoi(line); break;
				case 12: repeatDelay = sf::milliseconds(stoi(line)); break;
				case 13: repeatSpeed = sf::milliseconds(stoi(line)); break;
				case 14: piecerotation[0] = stoi(line); break;
				case 15: piecerotation[1] = stoi(line); break;
				case 16: piecerotation[2] = stoi(line); break;
				case 17: piecerotation[3] = stoi(line); break;
				case 18: piecerotation[4] = stoi(line); break;
				case 19: piecerotation[5] = stoi(line); break;
				case 20: piecerotation[6] = stoi(line); break;
				case 21: name = line; break;
				case 22: currentmode = stoi(line); break;
				case 23: MusicVolume = stoi(line); break;
				case 24: EffectVolume = stoi(line); break;
				case 25: ChatVolume = stoi(line); break;
				case 26: sound = stoi(line); break;
				case 27: repeatDelayDown = sf::milliseconds(stoi(line)); break;
				case 28: repeatSpeedDown = sf::milliseconds(stoi(line)); break;
				case 29: frameDelay = sf::microseconds(stoi(line)); break;
				case 30: inputDelay = sf::microseconds(stoi(line)); break;
				case 31: vSync = stoi(line); break;
				case 32: absolutePlacement = stoi(line); break;
				case 33: c0r0 = sf::Keyboard::Key(stoi(line)); break;
				case 34: c1r0 = sf::Keyboard::Key(stoi(line)); break;
				case 35: c2r0 = sf::Keyboard::Key(stoi(line)); break;
				case 36: c3r0 = sf::Keyboard::Key(stoi(line)); break;
				case 37: c4r0 = sf::Keyboard::Key(stoi(line)); break;
				case 38: c5r0 = sf::Keyboard::Key(stoi(line)); break;
				case 39: c6r0 = sf::Keyboard::Key(stoi(line)); break;
				case 40: c7r0 = sf::Keyboard::Key(stoi(line)); break;
				case 41: c8r0 = sf::Keyboard::Key(stoi(line)); break;
				case 42: c9r0 = sf::Keyboard::Key(stoi(line)); break;
				case 43: c0r1 = sf::Keyboard::Key(stoi(line)); break;
				case 44: c1r1 = sf::Keyboard::Key(stoi(line)); break;
				case 45: c2r1 = sf::Keyboard::Key(stoi(line)); break;
				case 46: c3r1 = sf::Keyboard::Key(stoi(line)); break;
				case 47: c4r1 = sf::Keyboard::Key(stoi(line)); break;
				case 48: c5r1 = sf::Keyboard::Key(stoi(line)); break;
				case 49: c6r1 = sf::Keyboard::Key(stoi(line)); break;
				case 50: c7r1 = sf::Keyboard::Key(stoi(line)); break;
				case 51: c8r1 = sf::Keyboard::Key(stoi(line)); break;
				case 52: c9r1 = sf::Keyboard::Key(stoi(line)); break;
				case 53: c0r2 = sf::Keyboard::Key(stoi(line)); break;
				case 54: c1r2 = sf::Keyboard::Key(stoi(line)); break;
				case 55: c2r2 = sf::Keyboard::Key(stoi(line)); break;
				case 56: c3r2 = sf::Keyboard::Key(stoi(line)); break;
				case 57: c4r2 = sf::Keyboard::Key(stoi(line)); break;
				case 58: c5r2 = sf::Keyboard::Key(stoi(line)); break;
				case 59: c6r2 = sf::Keyboard::Key(stoi(line)); break;
				case 60: c7r2 = sf::Keyboard::Key(stoi(line)); break;
				case 61: c8r2 = sf::Keyboard::Key(stoi(line)); break;
				case 62: c9r2 = sf::Keyboard::Key(stoi(line)); break;
				case 63: c0r3 = sf::Keyboard::Key(stoi(line)); break;
				case 64: c1r3 = sf::Keyboard::Key(stoi(line)); break;
				case 65: c2r3 = sf::Keyboard::Key(stoi(line)); break;
				case 66: c3r3 = sf::Keyboard::Key(stoi(line)); break;
				case 67: c4r3 = sf::Keyboard::Key(stoi(line)); break;
				case 68: c5r3 = sf::Keyboard::Key(stoi(line)); break;
				case 69: c6r3 = sf::Keyboard::Key(stoi(line)); break;
				case 70: c7r3 = sf::Keyboard::Key(stoi(line)); break;
				case 71: c8r3 = sf::Keyboard::Key(stoi(line)); break;
				case 72: c9r3 = sf::Keyboard::Key(stoi(line)); break;
			}
			countset++;
		}
		file.close();
	}
	else
		success = 0;

	if (countset!=32)
		success = 0;

	if (!success) {
		cout << "loadOptions failed, setting default options" << endl;
		down = sf::Keyboard::K;
		left = sf::Keyboard::J;
		right = sf::Keyboard::L;
		rcw = sf::Keyboard::F;
		rccw = sf::Keyboard::D;
		r180 = sf::Keyboard::A;
		hd = sf::Keyboard::Space;
		chat = sf::Keyboard::LControl;
		score = sf::Keyboard::LShift;
		away = sf::Keyboard::F4;

		c0r0 = sf::Keyboard::A;
		c1r0 = sf::Keyboard::S;
		c2r0 = sf::Keyboard::D;
		c3r0 = sf::Keyboard::F;
		c4r0 = sf::Keyboard::G;
		c5r0 = sf::Keyboard::H;
		c6r0 = sf::Keyboard::J;
		c7r0 = sf::Keyboard::K;
		c8r0 = sf::Keyboard::L;
		c9r0 = sf::Keyboard::Tilde;
		c0r1 = sf::Keyboard::Z;
		c1r1 = sf::Keyboard::X;
		c2r1 = sf::Keyboard::C;
		c3r1 = sf::Keyboard::V;
		c4r1 = sf::Keyboard::B;
		c5r1 = sf::Keyboard::N;
		c6r1 = sf::Keyboard::M;
		c7r1 = sf::Keyboard::Comma;
		c8r1 = sf::Keyboard::Period;
		c9r1 = sf::Keyboard::Dash;
		c0r2 = sf::Keyboard::Num1;
		c1r2 = sf::Keyboard::Num2;
		c2r2 = sf::Keyboard::Num3;
		c3r2 = sf::Keyboard::Num4;
		c4r2 = sf::Keyboard::Num5;
		c5r2 = sf::Keyboard::Num6;
		c6r2 = sf::Keyboard::Num7;
		c7r2 = sf::Keyboard::Num8;
		c8r2 = sf::Keyboard::Num9;
		c9r2 = sf::Keyboard::Num0;
		c0r3 = sf::Keyboard::Q;
		c1r3 = sf::Keyboard::W;
		c2r3 = sf::Keyboard::E;
		c3r3 = sf::Keyboard::R;
		c4r3 = sf::Keyboard::T;
		c5r3 = sf::Keyboard::Y;
		c6r3 = sf::Keyboard::U;
		c7r3 = sf::Keyboard::I;
		c8r3 = sf::Keyboard::O;
		c9r3 = sf::Keyboard::P;

		ghostpiece = true;
		fullscreen = false;
		vSync = false;
		absolutePlacement = true;

		repeatDelay = sf::milliseconds(150);
		repeatSpeed = sf::milliseconds(0);

		repeatDelayDown = sf::milliseconds(20);
		repeatSpeedDown = sf::milliseconds(20);

		//frame delay multiplicator 10 = 100 FPS
		frameDelay = sf::milliseconds(10);
        //input delay multiplicator 1000 = 1000 microseconds - 1ms
		inputDelay = sf::milliseconds(1);

		piecerotation[0] = 3;
		piecerotation[1] = 1;
		piecerotation[2] = 3;
		piecerotation[3] = 1;
		piecerotation[4] = 1;
		piecerotation[5] = 2;
		piecerotation[6] = 0;



		name="Player";
		currentmode=-1;
		MusicVolume=100;
		EffectVolume=100;
		ChatVolume=100;
		sound=true;
	}
}

void optionSet::saveOptions() {
	ofstream file(resourcePath() + "options.cfg", ios::trunc);

	cout << "Saving options..." << endl;

	if (file.is_open()) {
		file << down << endl;
		file << left << endl;
		file << right << endl;
		file << rcw << endl;
		file << rccw << endl;
		file << r180 << endl;
		file << hd << endl;
		file << chat << endl;
		file << score << endl;
		file << away << endl;
		file << ghostpiece << endl;
		file << fullscreen << endl;
		file << repeatDelay.asMilliseconds() << endl;
		file << repeatSpeed.asMilliseconds() << endl;
		for (int x=0; x<7; x++)
			file << (int)piecerotation[x] << endl;
		file << name.toAnsiString() << endl;
		file << currentmode << endl;
		file << MusicVolume << endl;
		file << EffectVolume << endl;
		file << ChatVolume << endl;
		file << sound << endl;
		file << repeatDelayDown.asMilliseconds() << endl;
		file << repeatSpeedDown.asMilliseconds() << endl;
		file << frameDelay.asMicroseconds() << endl;
		file << inputDelay.asMicroseconds() << endl;
		file << vSync << endl;
		file << absolutePlacement << endl;
		file << c0r0 << endl;
		file << c1r0 << endl;
		file << c2r0 << endl;
		file << c3r0 << endl;
		file << c4r0 << endl;
		file << c5r0 << endl;
		file << c6r0 << endl;
		file << c7r0 << endl;
		file << c8r0 << endl;
		file << c9r0 << endl;
		file << c0r1 << endl;
		file << c1r1 << endl;
		file << c2r1 << endl;
		file << c3r1 << endl;
		file << c4r1 << endl;
		file << c5r1 << endl;
		file << c6r1 << endl;
		file << c7r1 << endl;
		file << c8r1 << endl;
		file << c9r1 << endl;
		file << c0r2 << endl;
		file << c1r2 << endl;
		file << c2r2 << endl;
		file << c3r2 << endl;
		file << c4r2 << endl;
		file << c5r2 << endl;
		file << c6r2 << endl;
		file << c7r2 << endl;
		file << c8r2 << endl;
		file << c9r2 << endl;
		file << c0r3 << endl;
		file << c1r3 << endl;
		file << c2r3 << endl;
		file << c3r3 << endl;
		file << c4r3 << endl;
		file << c5r3 << endl;
		file << c6r3 << endl;
		file << c7r3 << endl;
		file << c8r3 << endl;
		file << c9r3;
	}
	else
		cout << "Failed" << endl;
}

void optionSet::initBasePieces() {
	short value[112] = { 0, 4, 0, 0,
						 0, 4, 0, 0,
						 0, 4, 4, 0,
						 0, 0, 0, 0,

						 0, 3, 0, 0,
						 0, 3, 0, 0,
						 3, 3, 0, 0,
						 0, 0, 0, 0,

						 0, 5, 0, 0,
						 0, 5, 5, 0,
						 0, 0, 5, 0,
						 0, 0, 0, 0,

						 0, 7, 0, 0,
						 7, 7, 0, 0,
						 7, 0, 0, 0,
						 0, 0, 0, 0,

						 0, 2, 0, 0,
						 0, 2, 0, 0,
						 0, 2, 0, 0,
						 0, 2, 0, 0,

						 0, 0, 0, 0,
						 1, 1, 1, 0,
						 0, 1, 0, 0,
						 0, 0, 0, 0,

						 0, 0, 0, 0,
						 0, 6, 6, 0,
						 0, 6, 6, 0,
						 0, 0, 0, 0 };

	short vc=0;

	for (int p=0; p<7; p++) {
		basepiece[p].posX=0;
		basepiece[p].posY=0;
		basepiece[p].lpiece=false;
		basepiece[p].rotation=piecerotation[p];
		for (int y=0; y<4; y++)
			for (int x=0; x<4; x++) {
				basepiece[p].grid[y][x] = value[vc];
				if (value[vc])
					basepiece[p].tile=value[vc];
				vc++;
			}
	}
	basepiece[4].lpiece=true;
	basepiece[6].lpiece=true;
}

void optionSet::getVideoModes() {
	std::vector<sf::VideoMode> allmodes = sf::VideoMode::getFullscreenModes();
	bool add=true;
    for (std::size_t i = 0; i < allmodes.size(); ++i) {
    	for (std::size_t p = 0; p<modes.size(); p++) {
    		if (allmodes[i].width == modes[p].width && allmodes[i].height == modes[p].height)
    			add=false;
    	}
    	if (add)
    		modes.push_back(allmodes[i]);
    	add=true;
    }
}

void optionSet::setDelay(short i, sf::String string) {
	short value;
	if (string.getSize() > 0)
		value = stoi(string.toAnsiString());
	else
		value = 0;
	if (i == 1)
		repeatDelay = sf::milliseconds(value);
	else if (i == 2)
		repeatSpeed = sf::milliseconds(value);
	else if (i == 3)
		repeatDelayDown = sf::milliseconds(value);
	else if (i == 4)
		repeatSpeedDown = sf::milliseconds(value);
	else if (i == 5) {
		if (value)
			frameDelay = sf::milliseconds(1000/value);
	}
	else if (i == 6)
		inputDelay = sf::microseconds(value);
}
