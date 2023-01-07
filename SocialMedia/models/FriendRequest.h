//
// Created by lolluckestar on 27.11.2022.
//

#ifndef PROIECT_FRIENDREQUEST_H
#define PROIECT_FRIENDREQUEST_H

#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

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
    FriendRequest(std::string json) {
        Json::Value jsonObj;
        Json::Reader reader;
        bool parsingSuccesful = reader.parse(json, jsonObj);
        if (parsingSuccesful) {
            id = jsonObj["id"].asInt();
            id1 = jsonObj["id1"].asInt();
            id2 = jsonObj["id2"].asInt();
            type = jsonObj["type"].asString();
            accepted = jsonObj["accepted"].asBool();
        }
    }

    std::string toJson() {
        Json::Value jsonObj;
        jsonObj["id"] = id;
        jsonObj["id1"] = id1;
        jsonObj["id2"] = id2;
        jsonObj["accepted"] = accepted;
        return jsonObj.toStyledString();
    }
};

#endif // PROIECT_FRIENDREQUEST_H
