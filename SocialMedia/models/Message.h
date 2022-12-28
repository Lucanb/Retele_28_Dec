//
// Created by lolluckestar on 27.11.2022.
//

#ifndef PROIECT_MESSAGE_H
#define PROIECT_MESSAGE_H

#include<iostream>
#include<string>

struct Message {
    int id;
    int chatId;

    std::string date;
    std::string message;

    Message(){
        this->chatId = 0;
        this->id = 0;
    }

    Message(
            int id,
            int chatId,
            std::string date,
            std::string message
    ){
        this->chatId = id;
        this->id = chatId;
        this->date=date;
        this->message=message;
    }
};





#endif //PROIECT_MESSAGE_H
