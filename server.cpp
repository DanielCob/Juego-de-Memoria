/**
 * @file server.cpp
 * @author Daniel Cob Beirute
 * @brief la clase servidor se encarga de manejar tanto la lógica del juego como la conexión con el cliente a traves de sockets.
 * @version 0.1
 * @date 2022-04-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include "paged_Matrix.cpp"
#define PORT 8080

using namespace std;

/**
 * @brief server_fd almacena el socket file del servidor, new_socket almacena el socket del cliente, valread almacena la cantidad de dígitos leídos del último mensaje
 *
 */
int server_fd, new_socket, valread;
/**
 * @brief almacena los mensajes enviados por el cliente
 *
 */
char buffer[1042] = {0};
const char *player1_name;
const char *player2_name;
/**
 * @brief almacena el turno, si el turno es del jugador 1 almacena 1, si es el turno del jugador 2 almacena 2
 *
 */
int turn;
int pointsP1 = 0;
int pointsP2 = 0;
/**
 * @brief almacena el multiplicador de puntaje para la suma de puntos
 *
 */
int multiplier = 1;
paged_Matrix m;

void initializeServer()
{
    struct sockaddr_in address = {};
    int opt = 1;
    int addrlen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 1) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    const char *hello = "Hello from server";
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");
}
/**
 * @brief lee el mensaje del cliente
 *
 * @return const char* mensaje
 */
const char *readSocket()
{
    memset(buffer, 0, valread);
    // cout << "Client: ";
    valread = read(new_socket, buffer, 1024);
    // cout << buffer << endl;
    return buffer;
}
/**
 * @brief envia al cliente un mensaje determinado
 *
 * @param msg
 */
void sendToClient(const char *msg)
{
    send(new_socket, msg, strlen(msg), 0);
    // cout << "Message sent: " << msg << endl;
}
/**
 * @brief lee los nombres enviados por el cliente y los almacena
 *
 */
void readNames()
{
    player1_name = readSocket();
    sendToClient(to_string(pointsP1).c_str());
    player2_name = readSocket();
    sendToClient(to_string(pointsP2).c_str());
}
/**
 * @brief define el orden de los turnos
 *
 */
void logicOrder()
{
    readSocket();
    srand(time(0));
    int i = (rand() % 2) + 1;
    turn = i;
    sendToClient(to_string(i).c_str());
}

/**
 * @brief pide a la matriz buscar una carta
 *
 * @param c posición de la carta en forma: i,j
 * @return string imagen que contiene la carta
 */
string readCard(const char *c)
{
    return m.getImage(m.seekCard(c[0] - 48, c[2] - 48)); //-48 sirve para convertir de ASCII a int
}
/**
 * @brief lee el mensaje del cliente y le envía la carta solicitada
 *
 */
void logicRevealCard()
{
    sendToClient(readCard(readSocket()).c_str());
}
/**
 * @brief añade puntos a los jugadores dependiendo del turno
 *
 */
void logicAddPoints()
{
    if (turn == 1)
    {
        if (m.get_inMemory())
        {
            pointsP1 += 100;
        }
        pointsP1 += 100 * multiplier;
    }
    else
    {
        if (m.get_inMemory())
        {
            pointsP2 += 100;
        }
        pointsP2 += 100 * multiplier;
    }
}
/**
 * @brief realiza un cambio de turno
 *
 */
void logicChangeTurn()
{
    if (turn == 1)
    {
        turn = 2;
    }
    else
    {
        turn = 1;
    }
}
/**
 * @brief secuencia de un turno completo para el juego de memoria
 *
 */
void logicTurn()
{
    logicRevealCard();
    logicRevealCard();
    multiplier = readSocket()[0] - 48; //-48 sirve para convertir de ASCII a int
    sendToClient("Ok");
    readSocket(); // Is Pair?
    if (m.isPairs())
    {
        logicAddPoints();
        sendToClient("1");
    }
    else
    {
        sendToClient("0");
    }
    readSocket(); // points?
    if (turn == 1)
    {
        sendToClient(to_string(pointsP1).c_str());
    }
    else
    {
        sendToClient(to_string(pointsP2).c_str());
    }
    m.set_inMemory(false);
    if ((string)readSocket() == "false")
    { // double turn?
        logicChangeTurn();
    }
    sendToClient("Ok");
}

long get_mem_usage() {
    struct rusage myusage;

    getrusage(RUSAGE_SELF, &myusage);
    return myusage.ru_maxrss;
}

int main(int argc, char const *argv[])
{
    // long baseline = get_mem_usage();
    // for (int i = 0; i < 100; i++)
    // {
    //     void *m = malloc(20*1024*1024);
    //     memset(m,0,20*1024*1024);
    //     printf("usage: %ld + %ld\n", baseline, get_mem_usage()-baseline);
    // }
    
    cout << "memory usage: " << get_mem_usage() << " bytes" << endl;
    initializeServer();
    cout << "memory usage: " << get_mem_usage() << " bytes" << endl;
    readNames();
    logicOrder();
    while (m.get_cardsLeft() != 0)
    {
        logicTurn();
        cout << "P1 points: "<< pointsP1 << endl;
        cout << "P2 points: "<< pointsP2 << endl;
        cout << "memory usage: " << get_mem_usage() << " bytes" << endl;
        cout << "-----------Next Turn-----------" << endl;
    }

    return 0;
}