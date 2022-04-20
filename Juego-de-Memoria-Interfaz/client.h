#ifndef CLIENT_H
#define CLIENT_H


class client
{
private:
    int sock;
    int valread;
    char buffer[18000];
public:
    client();
    void connectToServer();
    void sendToServer(const char *msg);
    const char* readSocket();
};

#endif // CLIENT_H
