#pragma once
#include <string>

static association associations[1000];

class association
{
public:
    std::string description = "";
    int Code = 0;
    association(int code, std::string desc)
    {
        this->description = desc;
        this->Code = code;
    }
};

void initErrors()
{
    //error (1-500)
    associations[0] = association(-1,"could not establish connection, can occur in the client.run function on the server side");
    associations[1] = association(-2,"error binding socket, can occur on server side in the client.run function on the server side");
    associations[2] = association(-3,"invalid connection, can occur in the client.run function after accepting a connection");
    associations[3] = association(-4,"file already exists, can occur in the create function of the filehandler.");
    associations[5] = association(-5,"error while creating socket, can occur on the client side");
    associations[6] = association(-6,"error while trying to connect to server, can occur on the client side");
    associations[500] = association(-999,"unkown error, can occur on frontend as well as on backend");
    //status (501- 1000)
    associations[501] = association(0,"default server status, operating as intended");
}

association getAssociation(int code)
{
    for(association I : associations)
    {
        if(I.Code == code)
        {
            return I;
        }
    }
    return association(-999, "no association with code " + std::to_string(code));
}