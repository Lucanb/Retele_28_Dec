//
// Created by lolluckestar on 11.12.2022.
//

#ifndef MODELS_USER_H
#define MODELS_USER_H


#include<iostream>
#include<string>

struct User {

    int id;
    bool isAdmin;

    std::string userName;
    std::string firstname;
    std::string lastname;
    std::string birthday;
    std::string accountCreationDate;
    std::string profileDescription;


    User()=default;

    User(
            int id,
            bool isAdmin,
            std::string userName,
            std::string firstname,
            std::string lastname,
            std::string birthday,
            std::string accountCreationDate,
            std::string profileDescription
    ){
        this->id=id;
        this->isAdmin=isAdmin;
        this->userName = userName;
        this->firstname = firstname;
        this->lastname = lastname;
        this->birthday = birthday;
        this->accountCreationDate = accountCreationDate;
        this->profileDescription = profileDescription;
    }
};

#endif //MODELS_USER_H
