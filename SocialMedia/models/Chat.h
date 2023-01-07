//
// Created by lolluckestar on 27.11.2022.
//

#ifndef PROIECT_CHAT_H
#define PROIECT_CHAT_H

#include<iostream>
#include<string>
#include<vector>
#include"Message.h"
#include <jsoncpp/json/json.h>

struct Chat {

    int idChat;
    std::vector<int> idList;
    std::vector<int> idMessages;
    std::string title;

    Chat() = default;


    Chat(
            int idChat,
            std::vector<int> pidMessages,
            std::vector<int> pidList,
            std::string ptitle
    ) {
        this->idChat = idChat;
        idList = pidList;
        idMessages = pidMessages;
        title = ptitle;
    }

    Chat(std::string json) {
        Json::Value jsonObj;
        Json::Reader reader;
        bool parsingSuccesful = reader.parse(json, jsonObj);
        if (parsingSuccesful) {
            idChat = jsonObj["idChat"].asInt();
            idList = jsonObj["idList"].asInt();
            idMessages = jsonObj["idMessages"].asString();
            title = jsonObj["title"].asString();
            lastname = jsonObj["lastname"].asString();
            birthday = jsonObj["birthday"].asString();
            accountCreationDate = jsonObj["accountCreationDate"].asString();
            profileDescription = jsonObj["profileDescription"].asString();
        }
    }

    std::string toJson() {
        Json::Value jsonObj;
        jsonObj["idChat"] = idChat;
        jsonObj["idList"] = idList;
        jsonObj["idMessages"] = idMessages;
        jsonObj["title"] = title;
        return jsonObj.toStyledString();
    }
};


#endif //PROIECT_CHAT_H
