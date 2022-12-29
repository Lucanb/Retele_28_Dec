//
// Created by lolluckestar on 27.11.2022.
//

#ifndef PROIECT_FRIEND_H
#define PROIECT_FRIEND_H

#include <iostream>
#include <string>

struct Friend
{
    int id;
    int id1;
    int id2;

    std::string type;

    Friend()
    {
        this->id = 0;
        this->id1 = 0;
        this->id2 = 0;
        this->type = "";
    }

    Friend(
        int id,
        int id1,
        int id2,
        std::string type)
    {
        this->id = id;
        this->id1 = id1;
        this->id2 = id2;
        this->type = type;
    }
};
#endif // PROIECT_FRIEND_H
