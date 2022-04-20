/**
 * @file client.cpp
 * @author yDaniel Cob Beirute
 * @brief la clase cliente se encarga de conectarse al sevidor, así como enviar y recibir mensajes
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "client.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#define PORT 8080

using namespace std;
/**
 * @brief socket del servidor
 * 
 */
int sock = 0;
/**
 * @brief valread almacena la cantidad de dígitos leídos del último mensaje
 * 
 */
int valread = 0;
/**
 * @brief almacena los mensajes enviados por el servidor
 *
 */
char buffer[19000] = {0};

client::client() {}

void client::connectToServer()
{
    struct sockaddr_in serv_addr;
    const char *hello = "Hello from client";
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
    }
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
}

void client::sendToServer(const char *msg)
{
    send(sock, msg, strlen(msg), 0);
    cout << "Client: " << msg << endl;
}

const char *client::readSocket()
{
    // cout << "Server: " << endl;
    memset(buffer, 0, valread);
    valread = read(sock, buffer, 19000);
    // cout << buffer << endl;
    return buffer;
}
