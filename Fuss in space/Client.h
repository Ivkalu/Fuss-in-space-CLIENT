#pragma once
#define WIN32_LEAN_AND_MEAN
#include "queue"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

//gcc Client.cpp -lWs2_32 -o Client && Client

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
//#define DEFAULT_ADDRESS "192.168.0.17"
//constexpr auto DEFAULT_ADDRESS = "25.89.62.137";



class Client
{
private:

    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL, * ptr = NULL, hints;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

public:



    int init();
    int sendMessege(const char* sendbuf, int size);
    int close();
    void update();

    ~Client()
    {
        close();
        closesocket(ConnectSocket);
        WSACleanup();
    }



};