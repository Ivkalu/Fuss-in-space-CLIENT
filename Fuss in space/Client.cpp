#pragma once
#include "Client.h"
#include "Defines.h"
#include "Game.h"
#include "SpriteOrganizer.h"


//0 for success,
//1 for failure
int Client::init() {

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        eprintf("WSAStartup failed with error: %d\n", iResult);
        return(1);
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    

    // Resolve the server address and port
    iResult = getaddrinfo(DEFAULT_ADDRESS, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        eprintf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return(1);
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            eprintf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return(1);
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        eprintf("Unable to connect to server!\n");
        WSACleanup();
        return(1);
    }

    // Set a mode to nonblocking
    u_long iMode = 1;
    iResult = ioctlsocket(ConnectSocket, FIONBIO, &iMode);
    if (iResult != NO_ERROR) {
        eprintf("ioctlsocket failed with error: %ld\n", iResult);
        WSACleanup();
        return(1);
    }
    
    cprintf("Client initialised!\n");
    return 0;
}


int Client::sendMessege(const char* sendbuf, int size) 
{
    static bool haveBeen = false;
    iResult = send(ConnectSocket, sendbuf, size, 0);
    if (iResult == SOCKET_ERROR) {
        if (!haveBeen) {
            eprintf("send failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
        }
        haveBeen = true;
        return(1);
    }
    //cprintf("Bytes Sent: %ld\n", iResult);
    return 0;

}

struct StoneSprite
{
    uint16_t ID;
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
};

void Client::update() {
    while (recv(ConnectSocket, recvbuf, 1, 0) > 0) {

        switch (recvbuf[0]) {
        case C_JOINED_LOBBY:
            cprintf("Joined lobby!\n");
            spriteOrganizer->kill();
            spriteOrganizer->waitingMenuC->init();
            break;
        case C_GAME_STARTED:
            cprintf("Game started!\n");
            spriteOrganizer->kill();
            spriteOrganizer->gameMenuC->init();
            break;
        case C_LEAVE_LOBBY:
            cprintf("Left lobby!\n");
            spriteOrganizer->kill();
            spriteOrganizer->mainMenuC->init();
            break;
        case C_GAME_DATA:
        {
            iResult = recv(ConnectSocket, recvbuf, 1, 0);
            int maxLen = (uint8_t)(*recvbuf);
            spriteOrganizer->gameMenuC->clear();
            for (int i = 0; i < maxLen; i++)
            {
                iResult = recv(ConnectSocket, recvbuf, sizeof(StoneSprite), 0);
                Message<StoneSprite> d;
                memcpy(d.data_ptr, recvbuf, sizeof(StoneSprite));
                
                switch (d.data.ID) {
                case(1):
                    spriteOrganizer->gameMenuC->addSprite<Sprite>("assets/NULL.png", nullptr, new SDL_Rect{ d.data.x, d.data.y, d.data.w, d.data.h });
                    break;
                case(2):
                    spriteOrganizer->gameMenuC->addSprite<Sprite>("assets/NULL.png", nullptr, new SDL_Rect{ d.data.x, d.data.y, d.data.w, d.data.h });
                    break;
                case(3):
                    spriteOrganizer->gameMenuC->addSprite<Sprite>("assets/NULL.png", nullptr, new SDL_Rect{ d.data.x, d.data.y, d.data.w, d.data.h });
                    break;
                case(4):
                    spriteOrganizer->gameMenuC->addSprite<Sprite>("assets/Characters/Rat/Rat1.png", nullptr, new SDL_Rect{ d.data.x, d.data.y, d.data.w, d.data.h });
                    break;
                }
            }

            break;
        }
        case C_LOBBY_ALREADY_EXISTS:
            cprintf("Lobby already exists!\n");
            break;
        case C_LOBBY_DOESNT_EXIST:
            cprintf("Lobby doesn't exist!\n");
            break;
        case C_NOT_JOIN:
            cprintf("Couldn't join lobby!\n");
            break;
        case C_LOBBY_DATA:
            iResult = recv(ConnectSocket, recvbuf, 40, 0);
            spriteOrganizer->Playr1TextBox->setContent(std::string(recvbuf));
            spriteOrganizer->Playr2TextBox->setContent(std::string(recvbuf + 10));
            spriteOrganizer->Playr3TextBox->setContent(std::string(recvbuf + 20));
            spriteOrganizer->Playr4TextBox->setContent(std::string(recvbuf + 30));
            break;
        default:
            break;
        }

    }
}


int Client::close()
{
    
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        eprintf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return(1);
    }

    return 0;

}