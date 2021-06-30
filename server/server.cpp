#pragma once
#include <string>
#include <list>
#include <projectX/tools/strings.cpp>
#include <projectX/sysout/sysout.cpp>
#include <projectX/cryptography/cryptography.cpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/**
* @brief this needs to point to a function and needs to have a return value of type std::string else this whole thing won't work
*/
static std::string (*interpreter)(std::string*,std::string*);
static int buffersize = 1024;
static int lastcl = 0;
static std::string lastip = "";
static bool wait = 0;
static void sigpipehandler(int signum)
{
    sysError("sigpipe :: lost connection to client");
}
static void *run(void *tid)
{
    int cl = lastcl;
    std::string ip = lastip;
    lastcl = 0;
    char buffer[buffersize];
    std::string msg = "200";
    strcpy(buffer, msg.c_str());
    send(cl, buffer, buffersize, 0);
    while(cl > 0)
    {
        std::string null = "NULL";
        strcpy(buffer, null.c_str());
        recv(cl, buffer, buffersize, 0);
        msg = buffer;
        sysInfo("recv : " + msg);
        msg = ip + msg;
        if(buffer[0] == 'N')
        {if(buffer[1] == 'U')
        {if(buffer[2] == 'L')
        {if(buffer[3] == 'L')
        {sysError("exiting connection");pthread_exit(NULL);break;}
        }}}
        msg = interpreter(&msg,&ip);
        sysInfo("sending : " + msg);
        strcpy(buffer, msg.c_str());
        send(cl, buffer, buffersize, 0);
    }
    sysWarn("connection closed...");
    pthread_exit(NULL);
}
class server
{
public:
    //std::list<client> clients;
    std::list<std::string> blacklist;
    int buffersize = 8192;
    int port = 0;
    bool running = 1;

    /**
     * @brief Construct a new server object
     * 
     * @param p port the server runs on
     */
    server(int p,std::string interpretfunct(std::string*,std::string*),int bufsize)
    {
        buffersize = bufsize;
        sysInfo("starting up server at port " + std::to_string(p) + " with buffer size " + std::to_string(buffersize));
        // setting up sigpipe handler to prevent the server from crashing on sigpipe signal (broken pipe(client not disconnecting properly(terminated,powerloss,etc.)))
        signal(SIGPIPE, sigpipehandler);
        initchararray();
        interpreter = interpretfunct;
        this->port = p;
        int i = 0;
        struct sockaddr_in server_addr;
        socklen_t size;
        int remote = socket(AF_INET, SOCK_STREAM, 0);
        if(remote < 0)
        {
            sysError("could not establish connection :: error-code 1");
        }
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htons(INADDR_ANY);
        server_addr.sin_port = htons(this->port);
        if((bind(remote, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0)
        {
            sysError("Error binding connection (socket has been established)");
        }
        size = sizeof(server_addr);
        sysInfo("listening...");
        listen(remote, 1);
        while(this->running)
        {
            while(wait){}
            int cl = accept(remote, (struct sockaddr *)&server_addr,&size);
            if(cl < 0)
            {
                sysError("connection invalid");
            }
            lastcl = cl;
            struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&server_addr;
            struct in_addr ipAddr = pV4Addr->sin_addr;
            char str[INET_ADDRSTRLEN];
            lastip = inet_ntop(AF_INET, &ipAddr, str, INET_ADDRSTRLEN);
            sysInfo(lastip + " accepted");
            pthread_t ncThread;
            long tid = ++i;
            pthread_create(&ncThread,NULL,run,(void *)tid);
        }
    }

    /**
     * @brief blacklists a IPv4 from connecting to this server for the current session, resets on restart, 
     * also disconnects the client
     * 
     * @param IPv4 
     */
    void addtoblacklist(std::string IPv4)
    {
        this->dropClient(IPv4);
        this->blacklist.push_back(IPv4);
    }

    /**
     * @brief drops a single client
     * 
     * @param IPv4 
     */
    void dropClient(std::string IPv4)
    {
    }
};