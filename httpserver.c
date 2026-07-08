#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#pragma comment(lib, "ws2_32.lib")

int main(void)
{
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        printf("winsock failed\n");
        return 1;
    }

    printf("server starting...\n");

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == INVALID_SOCKET)
    {
        printf("socket creation failed\n");
        WSACleanup();
        return 1;
    }

    printf("socket created!\n");

    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr*)&server_address,
             sizeof(server_address)) == SOCKET_ERROR)
    {
        printf("bind failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("server bound to port 8080!\n");

    if (listen(server_socket, 5) == SOCKET_ERROR)
    {
        printf("listen failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("server listening...\n");

    SOCKET client_socket = accept(server_socket, NULL, NULL);

    if (client_socket == INVALID_SOCKET)
    {
        printf("accept failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("client connected!\n");

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
