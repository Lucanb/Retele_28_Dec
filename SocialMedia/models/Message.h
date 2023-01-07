//
// Created by lolluckestar on 27.11.2022.
//

#ifndef PROIECT_MESSAGE_H
#define PROIECT_MESSAGE_H

#include<iostream>
#include<string>
#include <jsoncpp/json/json.h>

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
    Message(std::string json) {
        Json::Value jsonObj;
        Json::Reader reader;
        bool parsingSuccesful = reader.parse(json, jsonObj);
        if (parsingSuccesful) {
            id = jsonObj["id"].asInt();
            chatId = jsonObj["chatId"].asInt();
            date = jsonObj["date"].asString();
            message = jsonObj["message"].asString();
        }
    }

    std::string toJson() {
        Json::Value jsonObj;
        jsonObj["id"] = id;
        jsonObj["chatId"] = chatId;
        jsonObj["date"] = date;
        jsonObj["message"] = message;
        return jsonObj.toStyledString();
    }
};





#endif //PROIECT_MESSAGE_H
