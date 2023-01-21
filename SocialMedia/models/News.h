//
// Created by lolluckestar on 27.11.2022.
//

#ifndef PROIECT_NEWS_H
#define PROIECT_NEWS_H

#include <iostream>
#include <string>

#include <jsoncpp/json/json.h>

struct News {
    int id;
    int authorId;

    std::string title;
    std::string content;
    std::string type;


    News() = default;

    News(
            int id,
            int authorId,
            std::string title,
            std::string content,
            std::string type
    ) {
        this->id = id;
        this->authorId = authorId;
        this->title = title;
        this->content = content;
        this->type = type;
    }

    News(std::string json) {
        Json::Value jsonObj;
        Json::Reader reader;
        bool parsingSuccesful = reader.parse(json, jsonObj);
        if (parsingSuccesful) {
            authorId = jsonObj["authorId"].asInt();
            title = jsonObj["title"].asString();
            content = jsonObj["content"].asString();
            type = jsonObj["type"].asString();
            id = jsonObj["id"].asInt();
        }
    }

    std::string toJson() {
        Json::Value jsonObj;
        jsonObj["id"] = id;
        jsonObj["title"] = title;
        jsonObj["authorId"] = authorId;
        jsonObj["content"] = content;
        jsonObj["type"] = type;
        return jsonObj.toStyledString();
    }
};


#endif //PROIECT_NEWS_H
