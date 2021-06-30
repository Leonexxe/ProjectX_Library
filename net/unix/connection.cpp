#pragma once
#include <string>
#include <list>
#include <projectX/tools/strings.cpp>
#include <projectX/sysout.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <projectX/net/addr.cpp>
#include <pthread.h>

static std::string* tempdatainpointer;
static int buffersize = 8192;
static int lastclient = 0;
static int last_sleep_ms = 0;
static int threads = 0;
static std::string (*interpreter)(std::string*);
static void *conv_loop(void *tid)
{
    std::string* data_send = tempdatainpointer;
    char buffer[buffersize];
    int client = lastclient;
    int sleep_ms = last_sleep_ms;
    recv(client, buffer, buffersize, 0);
    sysInfo("received 200 from server");
    while(1)
    {
        while(*data_send == ""){};
        const char* temp = data_send->c_str();
        strcpy(buffer, temp);
        sysInfo("sending " + *data_send);
        *data_send = "";
        send(client, buffer, buffersize, 0);
        recv(client, buffer, buffersize, 0);
        std::string msg = buffer;
        interpreter(&msg);
    }
    sysInfo("connection closed");
    pthread_exit(NULL);
}
class connection
{
public:
    addr connADDR;
    std::string data_send = "";
    /**
     * @brief Connect to a server
     * 
     * @param IPv4 
     * @param port 
     */
    connection(addr* ADDR, int sleep_ms, bool getnewthread,std::string interpreterfunct(std::string*))
    {
        interpreter = interpreterfunct;
        this->connADDR = *ADDR;
        int client;
        int port = ADDR->port;
        bool running = true;
        char* ip = "127.0.0.1";
        struct sockaddr_in server_addr;
        // init socket
        client = socket(AF_INET, SOCK_STREAM, 0);
        if(client < 0)
        {
            sysError("error creating socket");
            exit(-5);
        }
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_aton(ip, &server_addr.sin_addr);
        
        // connecting to server
        sysInfo("trying to connect to " + ADDR->IP + ":" + std::to_string(port));
        if(connect(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) >= 0)
        {
            sysInfo("connecting to server...");
        }
        else
        {
            sysError("could not connect to server");
            exit(-6);
        }
        sysInfo("connected");
        //
        tempdatainpointer = &this->data_send;
        last_sleep_ms = sleep_ms;
        pthread_t ncThread;
        long tid = ++threads;
        pthread_create(&ncThread,NULL,conv_loop,(void *)tid);
    }
    connection(){}
    /**
     * @brief closes the connection
     */
    void close()
    {
    }
};