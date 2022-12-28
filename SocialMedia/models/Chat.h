//
// Created by lolluckestar on 27.11.2022.
//

#ifndef PROIECT_CHAT_H
#define PROIECT_CHAT_H

#include<iostream>
#include<string>
#include<vector>
#include"Message.h"

struct Chat {

    int idChat;
    std::vector<int> idList;
    std::vector<int> idMessages;
    std::string title;

    Chat()=default;


    Chat(
            int idChat,
            std::vector <int> pidMessages,
            std::vector <int> pidList,
            std::string ptitle
    ){
        this->idChat=idChat;
        idList = pidList;
        idMessages = pidMessages;
        title = ptitle;
    }

};


#endif //PROIECT_CHAT_H
