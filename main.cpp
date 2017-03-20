#define SFML_NO_DEPRECATED_WARNINGS
#include <SFML/Graphics.hpp>
#include "gamePlay.h"
#include "textures.h"
#include "sounds.h"
#include "gui.h"
#include "network.h"
#include "packetcompress.h"
#include <iostream> // just here for quick and simple error testing, remove if you want
#include <TGUI/TGUI.hpp>
#include <sstream>

#ifdef __APPLE__
#include "ResourcePath.hpp"
#else
#include "EmptyResourcePath.h"
#endif

using namespace std;

#define CLIENT_VERSION 1

void resizeWindow(sf::View& view, sf::Event& event) {
    float ratio;
    if ((float)event.size.width/event.size.height > 960.0/600) {
        ratio = (event.size.height * (960.0/600)) / event.size.width;
        view.setViewport(sf::FloatRect((1-ratio)/2.0, 0, ratio, 1));
    }
    else {
        ratio = (event.size.width / (960.0/600)) / event.size.height;
        view.setViewport(sf::FloatRect(0, (1-ratio)/2.0, 1, ratio));
    }
}

int main()
{
    sf::Font typewriter, printFont;
    typewriter.loadFromFile(resourcePath() + "media/Kingthings Trypewriter 2.ttf");
    printFont.loadFromFile(resourcePath() + "media/F25_Bank_Printer.ttf");

    enum gamestates { MainMenu, CountDown, Game, GameOver };
    gamestates gamestate = MainMenu;

    textures textureBase;
    textureBase.loadTextures();

    network net;

    soundBank sounds;

    srand(time(NULL));

    gamePlay game(&textureBase, &sounds, &typewriter);

    game.field.setName(game.options.name, printFont);

    sounds.setEffectVolume(game.options.EffectVolume);
    sounds.setMusicVolume(game.options.MusicVolume);
    sounds.setChatVolume(game.options.ChatVolume);

    sf::RenderWindow window;
    if (game.options.fullscreen)
        window.create(game.options.modes[game.options.currentmode], "SpeedBlocks", sf::Style::Fullscreen);
    if (!window.isOpen()) {
        window.create(sf::VideoMode(960, 600), "SpeedBlocks");
        //window.create(sf::VideoMode(544, 340), "SpeedBlocks");
        game.options.fullscreen=false;
        game.options.currentmode=-1;
    }
    sf::View view(sf::FloatRect(0, 0, 960, 600));
    window.setView(view);

    GameFieldDrawer gui(window, typewriter, printFont, game.options, sounds, game, net, textureBase);
    gui.clientVersion = CLIENT_VERSION;

    gui.gui.setView(view);

    sf::Clock frameClock;
    sf::Time current=sf::seconds(0), nextDraw=sf::seconds(0);

    while (window.isOpen())
    {
        sf::Event event;
        switch (gamestate) {
            case MainMenu:
                while (window.pollEvent(event))
                {
                    gui.handleEvent(event);
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::Resized && gui.options->currentmode == -1) {
                        resizeWindow(view, event);
                        window.setView(view);
                        gui.gui.setView(view);
                    }
                }
                if (gui.inroom)
                    gamestate=GameOver;
                if (gui.training) {
                    gui.training=false;
                    gui.gui.get("MainMenu")->hide();
                    gui.gui.get("InGameTab")->show();
                    gui.gui.get("GameFields")->show();
                    gamestate = CountDown;
                    game.startCountdown();
                }
                if (gui.quit) {
                    window.close();
                }
                if (gui.playonline)
                    while (net.receiveData())
                            gui.handlePacket();

                if (gui.disconnect)
                    gui.disconnect=false;
            break;

            case CountDown:
                while (window.pollEvent(event)) {
                    gui.handleEvent(event);
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::Resized && gui.options->currentmode == -1) {
                        resizeWindow(view, event);
                        window.setView(view);
                        gui.gui.setView(view);
                    }
                    else if (event.type == sf::Event::KeyPressed && !gui.chatFocused) {
                        if (event.key.code == game.options.right)
                            game.rKey=true;
                        else if (event.key.code == game.options.left)
                            game.lKey=true;
                        else if (event.key.code == game.options.chat)
                            gui.Chat();
                        else if (event.key.code == game.options.score)
                            gui.Score();
                        else if (event.key.code == game.options.away && gui.playonline) {
                            if (gui.away)
                                gui.unAway();
                            else
                                gui.goAway();
                        }
                    }
                    else if (event.type == sf::Event::KeyReleased) {
                        if (event.key.code == game.options.right)
                            game.rKey=false;
                        else if (event.key.code == game.options.left)
                            game.lKey=false;
                    }
                }
                if (gui.playonline) {
                    while (net.receiveData())
                            gui.handlePacket();
                    if (gui.startgame) {
                        gui.linesSent=0;
                        gui.garbageCleared=0;
                        gui.linesBlocked=0;
                        game.startGame();
                        gamestate = Game;
                    }
                    if (gui.quit) {
                        gamestate= MainMenu;
                        gui.leaveRoom();
                        gui.quit=false;
                    }
                    if (gui.startcount)
                        gui.startcount=false;
                    if (gui.disconnect)
                        gamestate = MainMenu;
                }
                else if (gui.quit) {
                    gamestate = MainMenu;
                    gui.mainMenu();
                    gui.quit=false;
                }
                else if (game.countDown()) {
                    game.startGame();
                    gamestate = Game;
                }

                if (game.gameOver()) {
                    gamestate = GameOver;
                    gui.startgame=false;
                    gui.startcount=false;
                    //if (game.autoaway)
                    //    gui.goAway();
                    if (game.sendgameover)
                        gui.sendGameOver();
                    if (game.winner)
                        gui.sendGameWinner();
                }
            break;

            case Game:
                while (window.pollEvent(event))
                {
                    gui.handleEvent(event);
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::Resized && gui.options->currentmode == -1) {
                        resizeWindow(view, event);
                        window.setView(view);
                        gui.gui.setView(view);
                    }
                    else if (event.type == sf::Event::KeyPressed && !gui.chatFocused && !game.options.absolutePlacement) {
                        if (event.key.code == game.options.right)
                            game.mRKey();
                        else if (event.key.code == game.options.left)
                            game.mLKey();
                        else if (event.key.code == game.options.rcw)
                            game.rcw();
                        else if (event.key.code == game.options.rccw)
                            game.rccw();
                        else if (event.key.code == game.options.r180)
                            game.r180();
                        else if (event.key.code == game.options.down)
                            game.mDKey();
                        else if (event.key.code == game.options.hd)
                            game.hd();
                        else if (event.key.code == game.options.chat)
                            gui.Chat();
                        else if (event.key.code == game.options.score)
                            gui.Score();
                        else if (event.key.code == game.options.away && gui.playonline) {
                            if (gui.away)
                                gui.unAway();
                            else
                                gui.goAway();
                        }
                    }
					else if (event.type == sf::Event::KeyPressed && !gui.chatFocused && game.options.absolutePlacement) {
						if (event.key.code == game.options.c0r0)
							game.absolutePlacement(0, 0);
						if (event.key.code == game.options.c1r0)
							game.absolutePlacement(1, 0);
						if (event.key.code == game.options.c2r0)
							game.absolutePlacement(2, 0);
						if (event.key.code == game.options.c3r0)
							game.absolutePlacement(3, 0);
						if (event.key.code == game.options.c4r0)
							game.absolutePlacement(4, 0);
						if (event.key.code == game.options.c5r0)
							game.absolutePlacement(5, 0);
						if (event.key.code == game.options.c6r0)
							game.absolutePlacement(6, 0);
						if (event.key.code == game.options.c7r0)
							game.absolutePlacement(7, 0);
						if (event.key.code == game.options.c8r0)
							game.absolutePlacement(8, 0);
						if (event.key.code == game.options.c9r0)
							game.absolutePlacement(9, 0);
						if (event.key.code == game.options.c0r1)
							game.absolutePlacement(0, 1);
						if (event.key.code == game.options.c1r1)
							game.absolutePlacement(1, 1);
						if (event.key.code == game.options.c2r1)
							game.absolutePlacement(2, 1);
						if (event.key.code == game.options.c3r1)
							game.absolutePlacement(3, 1);
						if (event.key.code == game.options.c4r1)
							game.absolutePlacement(4, 1);
						if (event.key.code == game.options.c5r1)
							game.absolutePlacement(5, 1);
						if (event.key.code == game.options.c6r1)
							game.absolutePlacement(6, 1);
						if (event.key.code == game.options.c7r1)
							game.absolutePlacement(7, 1);
						if (event.key.code == game.options.c8r1)
							game.absolutePlacement(8, 1);
						if (event.key.code == game.options.c9r1)
							game.absolutePlacement(9, 1);
						if (event.key.code == game.options.c0r2)
							game.absolutePlacement(0, 2);
						if (event.key.code == game.options.c1r2)
							game.absolutePlacement(1, 2);
						if (event.key.code == game.options.c2r2)
							game.absolutePlacement(2, 2);
						if (event.key.code == game.options.c3r2)
							game.absolutePlacement(3, 2);
						if (event.key.code == game.options.c4r2)
							game.absolutePlacement(4, 2);
						if (event.key.code == game.options.c5r2)
							game.absolutePlacement(5, 2);
						if (event.key.code == game.options.c6r2)
							game.absolutePlacement(6, 2);
						if (event.key.code == game.options.c7r2)
							game.absolutePlacement(7, 2);
						if (event.key.code == game.options.c8r2)
							game.absolutePlacement(8, 2);
						if (event.key.code == game.options.c9r2)
							game.absolutePlacement(9, 2);
						if (event.key.code == game.options.c0r3)
							game.absolutePlacement(0, 3);
						if (event.key.code == game.options.c1r3)
							game.absolutePlacement(1, 3);
						if (event.key.code == game.options.c2r3)
							game.absolutePlacement(2, 3);
						if (event.key.code == game.options.c3r3)
							game.absolutePlacement(3, 3);
						if (event.key.code == game.options.c4r3)
							game.absolutePlacement(4, 3);
						if (event.key.code == game.options.c5r3)
							game.absolutePlacement(5, 3);
						if (event.key.code == game.options.c6r3)
							game.absolutePlacement(6, 3);
						if (event.key.code == game.options.c7r3)
							game.absolutePlacement(7, 3);
						if (event.key.code == game.options.c8r3)
							game.absolutePlacement(8, 3);
						if (event.key.code == game.options.c9r3)
							game.absolutePlacement(9, 3);
					}
                    else if (event.type == sf::Event::KeyReleased && !game.options.absolutePlacement) {
                        if (event.key.code == game.options.right)
                            game.sRKey();
                        else if (event.key.code == game.options.left)
                            game.sLKey();
                        else if (event.key.code == game.options.down)
                            game.sDKey();
                    }
                }
                game.delayCheck();

                if (gui.playonline) {
                    while (net.receiveData())
                            gui.handlePacket();
                    if (gui.quit) {
                        gamestate=MainMenu;
                        gui.leaveRoom();
                        gui.quit=false;
                        gui.startgame=false;
                    }
                    if (gui.disconnect) {
                        gamestate = MainMenu;
                        gui.startgame=false;
                    }
                    gui.sendGameData();
                }
                else if (gui.quit) {
                    gamestate = MainMenu;
                    gui.mainMenu();
                    gui.quit=false;
                }

                if (game.gameOver()) {
                    gamestate = GameOver;
                    gui.startgame=false;
                    //if (game.autoaway)
                    //    gui.goAway();
                    if (game.sendgameover)
                        gui.sendGameOver();
                    if (game.winner)
                        gui.sendGameWinner();
                }

                if (gui.startcount) {
                    gamestate=CountDown;
                    gui.startcount=false;
                    gui.startgame=false;
                    game.sRKey();
                    game.sLKey();
                    game.sDKey();
                }
            break;

            case GameOver:
                while (window.pollEvent(event))
                {
                    gui.handleEvent(event);
                    if (event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::Resized && gui.options->currentmode == -1) {
                        resizeWindow(view, event);
                        window.setView(view);
                        gui.gui.setView(view);
                    }
                    else if (event.type == sf::Event::KeyPressed && !gui.chatFocused) {
                        if (event.key.code == sf::Keyboard::Return && !gui.playonline) {
                            gamestate = CountDown;
                            game.startCountdown();
                            game.gameover=false;
                        }
                        else if (event.key.code == game.options.chat)
                            gui.Chat();
                        else if (event.key.code == game.options.score)
                            gui.Score();
                        else if (event.key.code == game.options.away && gui.playonline) {
                            if (gui.away)
                                gui.unAway();
                            else
                                gui.goAway();
                        }
                    }
                }
                if (gui.playonline) {
                    while (net.receiveData())
                            gui.handlePacket();
                    if (gui.startcount) {
                        gamestate=CountDown;
                        gui.startcount=false;
                        game.gameover=false;
                        game.sRKey();
                        game.sLKey();
                        game.sDKey();
                    }
                    if (gui.startgame) {
                        gui.linesSent=0;
                        gui.garbageCleared=0;
                        gui.linesBlocked=0;
                        game.startGame();
                        gamestate = Game;
                    }
                    if (gui.quit) {
                        gamestate= MainMenu;
                        gui.leaveRoom();
                        gui.quit=false;
                    }
                    if (gui.disconnect) {
                        gamestate = MainMenu;
                        game.gameover=false;
                    }
                    if (game.winner)
                        gui.sendGameWinner();
                }
                else if (gui.quit) {
                    gamestate = MainMenu;
                    gui.mainMenu();
                    gui.quit=false;
                }
            break;
        }

        current = frameClock.getElapsedTime();
        if (current > nextDraw || game.options.vSync) {
            nextDraw+=game.options.frameDelay;
            window.draw(textureBase.background);
            if (gamestate == CountDown || gamestate == Game || gamestate == GameOver) {
                window.draw( game.field.sprite );
                gui.drawFields();
            }
            gui.gui.draw();
            if (gui.adjPieces)
                for (int i=0; i<7; i++)
                    window.draw(gui.piece[i]);
            window.display();
        }
        else if (!game.options.vSync)
            sf::sleep(game.options.inputDelay);
        if (nextDraw < current)
            nextDraw=current;
    }

    game.options.saveOptions();

    return 0;
}