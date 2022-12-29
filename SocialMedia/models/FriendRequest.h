//
// Created by lolluckestar on 27.11.2022.
//

#ifndef PROIECT_FRIENDREQUEST_H
#define PROIECT_FRIENDREQUEST_H

#include <iostream>
#include <string>

struct FriendRequest
{
    int id;
    int id1;
    int id2;
    std::string type;
    bool accepted;

    FriendRequest()
    {
        this->id = 0;
        this->id1 = 0;
        this->id2 = 0;
        this->type = "";
        this->accepted = false;
    }

    FriendRequest(
        int id,
        int id1,
        int id2,
        std::string type,
        bool accepted)
    {
        this->id = id;
        this->id1 = id1;
        this->id2 = id2;
        this->type = type;
        this->accepted = accepted;
    }
};

#endif // PROIECT_FRIENDREQUEST_H
