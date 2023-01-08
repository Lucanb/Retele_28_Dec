//
// Created by lolluckestar on 07.01.2023.
//

#ifndef SOCIALMEDIA_PASSWORDS_H
#define SOCIALMEDIA_PASSWORDS_H

#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

struct Passwords {

    int id;
    std::string userName;
    std::string password;


    Passwords() = default;

    Passwords(
            int id, std::string userName, std::string password
    ) {
        this->id=id;
        this->userName=userName;
        this->password=password;
    }

    Passwords(std::string json) {
        Json::Value jsonObj;
        Json::Reader reader;
        bool parsingSuccesful = reader.parse(json, jsonObj);
        if (parsingSuccesful) {
            id = jsonObj["id"].asInt();
            userName = jsonObj["userName"].asString();
            password = jsonObj["password"].asString();
        }
    }

    std::string toJson() {
        Json::Value jsonObj;
        jsonObj["id"] = id;
        jsonObj["userName"] = userName;
        jsonObj["password"] = password;
        return jsonObj.toStyledString();
    }
};


#endif //SOCIALMEDIA_PASSWORDS_H
