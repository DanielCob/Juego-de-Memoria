#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include "paged_Matrix.cpp"
#define PORT 8080

using namespace std;

int server_fd, new_socket, valread;
char buffer[1042] = {0};
const char *player1_name;
const char *player2_name;
int pointsP1 = 0;
int pointsP2 = 0;
paged_Matrix m;

void initializeServer() {
    struct sockaddr_in address = {};
    int opt = 1;
    int addrlen = sizeof(address);
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    const char *hello = "Hello from server";
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");
}

const char* readSocket() {
    memset(buffer, 0, valread);
    cout << "Client: ";
    valread = read(new_socket, buffer, 1024);
    cout << buffer << endl;
    return buffer;
}

void sendToClient(const char* msg) {
    send(new_socket, msg, strlen(msg), 0);
    cout << "Message sent: " << msg << endl;
}

void readNames() {
    player1_name = readSocket();
    sendToClient(to_string(pointsP1).c_str());
    player2_name = readSocket();
    sendToClient(to_string(pointsP2).c_str());
}

void logicOrder() {
    readSocket();
    srand(time(0));
    int i = rand()%2;
    sendToClient(to_string(i).c_str());
}

string readCard(const char *c) {
    return m.getImage(m.seekCard(c[0]-48, c[2]-48)); //-48 sirve para convertir de ASCII a int
}

void logicRevealCard() {
    sendToClient(readCard(readSocket()).c_str());
}

void logicTurn() {
    logicRevealCard();
    logicRevealCard();
    //readSocket();
    //sendToClient(m.isPairs());   

}

int main(int argc, char const *argv[])
{
    initializeServer();
    readNames();
    logicOrder();
    while (true)
    {
        logicTurn();
    }

    return 0;
}