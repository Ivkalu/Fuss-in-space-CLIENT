#include "SpriteOrganizer.h"
#include "TextBox.h"
#include "Container.h"
#include <iostream>


SpriteOrganizer::SpriteOrganizer()
	:Container("assets/Background.png", nullptr, nullptr, true)
{

	addSprite(mainMenuC = new Container("", nullptr, nullptr, true));
	static Container* joinLobbyMenuC = addSprite<Container>("", nullptr, nullptr);
	static Container* createLobbyMenuC = addSprite<Container>("", nullptr, nullptr);
	addSprite(waitingMenuC = new Container("", nullptr, nullptr));
	addSprite(gameMenuC = new GameContainer());

	static Container* settingsC = addSprite<Container>("assets/NULL.png", nullptr, new SDL_Rect{ 300, 300, 500, 500 });

	addSprite<Button>("assets/NULL.png", nullptr, new SDL_Rect{ 1800,100,32,32 }, [] {
		settingsC->init();
		});



	// ****** SETTINGS ****** //

	settingsC->addSprite<Button>("assets/NULL.png", nullptr, new SDL_Rect{ 300 + 500,300,32,32 }, [] {
		settingsC->kill();
		});

	static TextBox* usernameTextBox = settingsC->addSprite<TextBox>(new SDL_Rect{ 300 + 200,300 + 100,44 * 5,16 * 5 });



	// ****** MAIN MENU ****** //

	mainMenuC->addSprite<Button>("assets/Buttons/JoinLobby.png", nullptr, new SDL_Rect{ 50,50,44 * 5,16 * 5 }, [] {
		joinLobbyMenuC->init();
		mainMenuC->kill();
		});

	mainMenuC->addSprite<Button>("assets/Buttons/CreateLobby.png", nullptr, new SDL_Rect{ 50,150,44 * 5,16 * 5 }, []() {
		mainMenuC->kill();
		createLobbyMenuC->init();
		});



	// ****** JOIN LOBBY MENU ****** //

	static TextBox* joinLobbyTextBox = joinLobbyMenuC->addSprite<TextBox>(new SDL_Rect{ 50,50,44 * 5,16 * 5 });
	joinLobbyMenuC->addSprite<Button>("assets/Buttons/Join.png", nullptr, new SDL_Rect{ 50,150,44 * 5,16 * 5 }, []() {
		uint8_t sendbuf[100] = {};
		uint8_t* sendbuf_ = sendbuf;

		uint8_t a[] = { S::S_JOIN_LOBBY };
		std::string lobbyName = joinLobbyTextBox->getContent();
		std::string playerName = usernameTextBox->getContent();
		uint8_t brawler[] = { 1 };

		memcpy(sendbuf_, a, 1);
		memcpy(sendbuf_ + 1, lobbyName.c_str(), lobbyName.length());
		memcpy(sendbuf_ + 11, playerName.c_str(), playerName.length());
		memcpy(sendbuf_ + 21, brawler, 1);

		const char* _sendbuf = (const char*)sendbuf;
		Game::client.sendMessege(_sendbuf, 22);
		});

	joinLobbyMenuC->addSprite<Button>("assets/Buttons/Back.png", nullptr, new SDL_Rect{ 50,250,44 * 5,16 * 5 }, []() {
		joinLobbyMenuC->kill();
		mainMenuC->init();
		});




	// ****** CREATE LOBBY MENU ****** //

	createLobbyMenuC->addSprite<Button>("assets/Buttons/Back.png", nullptr, new SDL_Rect{ 50,250,44 * 5,16 * 5 }, []() {
		createLobbyMenuC->kill();
		mainMenuC->init();
		});

	static TextBox* createLobbyTextBox = createLobbyMenuC->addSprite<TextBox>(new SDL_Rect{ 50,50,44 * 5,16 * 5 });
	createLobbyMenuC->addSprite<Button>("assets/Buttons/Start.png", nullptr, new SDL_Rect{ 50,150,44 * 5,16 * 5 }, []() {
		
		
		uint8_t sendbuf[100] = {};
		uint8_t* sendbuf_ = sendbuf;
		
		uint8_t a[] = { S::S_CREATE_LOBBY };
		std::string lobbyName = createLobbyTextBox->getContent();
		std::string playerName = usernameTextBox->getContent();
	
		uint8_t brawler[] = { 1 };

		memcpy(sendbuf_, a, 1);
		memcpy(sendbuf_ + 1, lobbyName.c_str(), lobbyName.length());
		memcpy(sendbuf_ + 11, playerName.c_str(), playerName.length());
		memcpy(sendbuf_ + 21, brawler, 1);

		const char* _sendbuf = (const char*)sendbuf;
		Game::client.sendMessege(_sendbuf, 22);
		});

	// ****** LOBBY WAITING MENU ****** //

	waitingMenuC->addSprite<Button>("assets/Buttons/Start.png", nullptr, new SDL_Rect{ 50,450,44 * 5,16 * 5 }, []() {
		uint8_t sendbuf[] = { S_START_GAME };
		Game::client.sendMessege((const char*)sendbuf, 1);
		});

	waitingMenuC->addSprite(Playr1TextBox = new TextBox(new SDL_Rect{ 50,50,44 * 5,16 * 5 }));
	waitingMenuC->addSprite(Playr2TextBox = new TextBox(new SDL_Rect{ 50,150,44 * 5,16 * 5 }));
	waitingMenuC->addSprite(Playr3TextBox = new TextBox(new SDL_Rect{ 50,250,44 * 5,16 * 5 }));
	waitingMenuC->addSprite(Playr4TextBox = new TextBox(new SDL_Rect{ 50,350,44 * 5,16 * 5 }));
	waitingMenuC->addSprite<Button>("assets/Buttons/Back.png", nullptr, new SDL_Rect{ 50,550,44 * 5,16 * 5 }, []() {
		uint8_t sendbuf[] = { S_LEAVE_LOBBY };
		Game::client.sendMessege((const char*)sendbuf, 1);
		});

	//mainMenuC->addSprite<Player>("assets/Characters/Rat/Rat1.png", NULL,  new SDL_Rect{ 500,500, 50, 100 });


}
Container* SpriteOrganizer::mainMenuC;

SpriteOrganizer* spriteOrganizer = nullptr;