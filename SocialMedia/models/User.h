//
// Created by lolluckestar on 11.12.2022.
//

#ifndef MODELS_USER_H
#define MODELS_USER_H


#include<iostream>
#include<string>
#include <jsoncpp/json/json.h>

struct User {

    int id;
    bool isAdmin;

    std::string userName;
    std::string firstname;
    std::string lastname;
    std::string birthday;
    std::string accountCreationDate;
    std::string profileDescription;


    User() = default;

    User(
            int id,
            bool isAdmin,
            std::string userName,
            std::string firstname,
            std::string lastname,
            std::string birthday,
            std::string accountCreationDate,
            std::string profileDescription
    ) {
        this->id = id;
        this->isAdmin = isAdmin;
        this->userName = userName;
        this->firstname = firstname;
        this->lastname = lastname;
        this->birthday = birthday;
        this->accountCreationDate = accountCreationDate;
        this->profileDescription = profileDescription;
    }

    User(std::string json) {
        Json::Value jsonObj;
        Json::Reader reader;
        bool parsingSuccesful = reader.parse(json, jsonObj);
        if (parsingSuccesful) {
            id = jsonObj["id"].asInt();
            isAdmin = jsonObj["isAdmin"].asInt();
            userName = jsonObj["userName"].asString();
            firstname = jsonObj["firstname"].asString();
            lastname = jsonObj["lastname"].asString();
            birthday = jsonObj["birthday"].asString();
            accountCreationDate = jsonObj["accountCreationDate"].asString();
            profileDescription = jsonObj["profileDescription"].asString();
        }
    }

    std::string toJson() {
        Json::Value jsonObj;
        jsonObj["id"] = id;
        jsonObj["isAdmin"] = isAdmin;
        jsonObj["userName"] = userName;
        jsonObj["firstname"] = firstname;
        jsonObj["birthday"] = birthday;
        jsonObj["accountCreationDate"] = accountCreationDate;
        jsonObj["profileDescription"] = profileDescription;
        return jsonObj.toStyledString();
    }
};


#endif //MODELS_USER_H
