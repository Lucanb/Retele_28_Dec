//
// Created by lolluckestar on 27.11.2022.
//

#ifndef PROIECT_FRIEND_H
#define PROIECT_FRIEND_H

#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

struct Friend {
    int id;
    int id1;
    int id2;

    std::string type;

    Friend() {
        this->id = 0;
        this->id1 = 0;
        this->id2 = 0;
        this->type = "";
    }

    Friend(
            int id,
            int id1,
            int id2,
            std::string type) {
        this->id = id;
        this->id1 = id1;
        this->id2 = id2;
        this->type = type;
    }

    Friend(std::string json) {
        Json::Value jsonObj;
        Json::Reader reader;
        bool parsingSuccesful = reader.parse(json, jsonObj);
        if (parsingSuccesful) {
            id = jsonObj["id"].asInt();
            id1 = jsonObj["id1"].asInt();
            id2 = jsonObj["id2"].asInt();
            type = jsonObj["type"].asString();
        }
    }

    std::string toJson() {
        Json::Value jsonObj;
        jsonObj["id"] = id;
        jsonObj["id1"] = id1;
        jsonObj["id2"] = id2;
        jsonObj["type"] = type;
        return jsonObj.toStyledString();
    }
};

#endif // PROIECT_FRIEND_H
