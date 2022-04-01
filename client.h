#ifndef client
#define client

class client
{
    int sock;

public:
    client();
    void connectToServer();
    void sendToServer(const char *msg);

};

#endif