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
#include "../nlohmann/json.hpp"

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
/*
    Chat(std::string json) {
        Json::Value jsonObj;
        Json::Reader reader;
        bool parsingSuccesful = reader.parse(json, jsonObj);
        if (parsingSuccesful) {
            idChat = jsonObj["idChat"].asInt();
         //   idList = jsonObj["idList"].as<std::vector<int>>();
         //   idMessages = jsonObj["idMessages"].as<std::vector<int>>();
            title = jsonObj["title"].asString();
            ///
        }
    }

    std::string toJson() {
        Json::Value jsonObj;
        jsonObj["idChat"] = idChat;
      //  jsonObj["idList"] = idList;
      //  jsonObj["idMessages"] = idMessages;
        jsonObj["title"] = title;
        return jsonObj.toStyledString();
    }
    */

    Chat(std::string jsonstring)
    {
        nlohmann::json j = nlohmann::json ::parse(jsonstring);
        idChat=j["idChat"];
        idList.assign(j["idList"].begin(), j["idList"].end());
        idMessages.assign(j["idMessages"].begin(), j["idMessages"].end());
        title=j["title"];

    }
    
    std::string toJson()
    {
        nlohmann::json j;
       j["idChat"]= idChat;
       j["title"] = title;
       j["idList"]=idList;
       j["idMessages"]=idMessages;
    }
};


#endif //PROIECT_CHAT_H
